/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:51 by tuzan             #+#    #+#             */
/*   Updated: 2025/01/25 18:17:51 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	server_err(const char *s)
{
	while (*s)
		write(2, s++, 1);
	exit(1);
}

static void	put_nbr(int n)
{
	if (n > 9)
		put_nbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

static void	put_str(const char *s)
{
	while (*s)
		write(1, s++, 1);
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	static t_signal	data = {0b00000000, 0b10000000};

	(void)context;
	if (signal == SIGUSR1)
		data.character += data.mask;
	data.mask >>= 1;
	if (data.mask == 0)
	{
		write(1, &data.character, 1);
		if (data.character == '\0')
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				server_err("Err: sending EOM signal");
		}
		data.mask = 128;
		data.character = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		server_err("Err: sending acknowledgment signal");
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
		server_err("Err:Handler setup failed");
	put_str("Server PID:");
	put_nbr(getpid());
	put_str("\nWaiting for message..\n");
	while (1)
		pause();
	return (0);
}
