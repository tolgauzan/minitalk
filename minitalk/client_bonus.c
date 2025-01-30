/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:49 by tuzan             #+#    #+#             */
/*   Updated: 2025/01/25 18:17:49 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_acknowledgment = 0;

static int	ft_atoi_num(const char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = (n * 10) + (*s - '0');
		s++;
	}
	return (n);
}

static void	client_err(const char *s)
{
	while (*s)
		write(2, s++, 1);
	exit(1);
}

static void	acknowledgment_handler(int signal)
{
	if (signal == SIGUSR1)
		g_acknowledgment = 1;
	if (signal == SIGUSR2)
		write(1, "Message acknowledged by server.\n", 32);
}

static void	send_signal(int server_pid, char ch)
{
	int	i;
	int	status;

	i = 7;
	while (i >= 0)
	{
		if ((ch >> i) & 1)
			status = kill(server_pid, SIGUSR1);
		else
			status = kill(server_pid, SIGUSR2);
		if (status < 0)
			client_err("Err: Failed to send signal\n");
		while (g_acknowledgment == 0)
			;
		g_acknowledgment = 0;
		i--;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;

	if (argc == 3)
	{
		server_pid = ft_atoi_num(argv[1]);
		if (server_pid <= 0)
			client_err("Err: Invalid PID!\n");
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = acknowledgment_handler;
		sa.sa_flags = 0;
		if (sigaction(SIGUSR1, &sa, NULL) < 0
			|| sigaction(SIGUSR2, &sa, NULL) < 0)
			client_err("Err:Handler setup failed");
		while (*argv[2])
			send_signal(server_pid, *argv[2]++);
		send_signal(server_pid, '\n');
		send_signal(server_pid, '\0');
	}
	else
		client_err("Err: Usage <Server PID> <Message>\n");
	return (0);
}
