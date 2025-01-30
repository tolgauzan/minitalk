/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:17:44 by tuzan             #+#    #+#             */
/*   Updated: 2025/01/25 18:17:44 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

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

static void	send_signal(int server_pid, char *msg)
{
	int	i;

	while (*msg)
	{
		i = 7;
		while (i >= 0)
		{
			if ((*msg >> i) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(500);
			i--;
		}
		msg++;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc == 3)
	{
		server_pid = ft_atoi_num(argv[1]);
		if (server_pid <= 0)
			client_err("Err: Invalid PID\n");
		send_signal(server_pid, argv[2]);
		send_signal(server_pid, "\n");
	}
	else
		client_err("Err: Usage <Server PID> <Message>\n");
	return (0);
}
