/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:02:43 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/08 18:41:47 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

static int	g_glob = 0;

int	check_arg(char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		if (av[1][i] < '0' || av[1][i] > '9')
			return (-1);
		i++;
	}
	i = ft_atoi(av[1]);
	return (i);
}

void	handler(int sig)
{
	(void)sig;
	g_glob = 1;
}

void	send_null(int pid, struct sigaction wait, char **msg)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		sigaction(SIGUSR1, &wait, NULL);
		while (g_glob == 0)
		{
			if (sleep(5) == 0)
			{
				free(*msg);
				exit(0);
			}
		}
		g_glob = 0;
		i++;
	}
}

void	process(int pid, char *msg, int i)
{
	struct sigaction	wait;

	while (msg[++i])
	{
		if (msg[i] == '0')
			kill(pid, SIGUSR1);
		if (msg[i] == '1')
			kill(pid, SIGUSR2);
		wait.sa_handler = &handler;
		if (sigemptyset(&(wait).sa_mask) == -1)
			exit(1);
		sigaddset(&(wait).sa_mask, SIGUSR1);
		wait.sa_flags = 0;
		sigaction(SIGUSR1, &wait, NULL);
		while (g_glob == 0)
		{
			if (sleep(5) == 0)
			{
				free(msg);
				exit(0);
			}
		}
		g_glob = 0;
	}
	send_null(pid, wait, &msg);
}

int	main(int ac, char **av)
{
	int	i;
	char	*msg;

	if (ac != 3)
		exit(0);
	i = check_arg(av);
	if (i < 2)
		exit(1);
	msg = get_bin(av[2]);
	if (!msg)
		exit(1);
	process(i, msg, -1);
	ft_putstr("recu\n");
	free(msg);
}
