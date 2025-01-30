/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:46 by tuzan             #+#    #+#             */
/*   Updated: 2025/01/25 18:17:46 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <signal.h>

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

static void	handler(int signal)
{
	static t_signal	data = {0, 0};

	if (signal == SIGUSR1)
		data.character |= (1 << (7 - data.counter));
	data.counter++;
	if (data.counter == 8)
	{
		write(1, &data.character, 1);
		data.character = 0;
		data.counter = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	put_str("Server PID: ");
	put_nbr(getpid());
	put_str("\nWaiting for message..\n");
	while (1)
		;
	return (0);
}
