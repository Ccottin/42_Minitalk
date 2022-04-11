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

//inverser get bin char et get char 

static int	g_glob = 0;

char	*get_bin_char(char c)
{
	static char	str[9];
	int	i;

	i = 7;
	while (i > -1)
	{
		if ((c & 1) == 1)
			str[i] = '1';
		else
			str[i] = '0';
		c >>= 1;
		i--;
	}
	return (str);
}


char	*get_bin(char *str)
{
	char	*ret;
	char	*temp;
	unsigned int	j;
	unsigned int	i;
	unsigned int	x;

	ret = ft_calloc((ft_strlen(str) * 8) + 2);
	if (!ret)
		return (NULL);
	x = 0;
	j = 0;
	while (str[j])
	{
		temp = get_bin_char(str[j]);
		i = 0;
		while (temp[i])
		{
			ret[x] = temp[i];
			x++;
			i++;
		}
		j++;
	}
	return (ret);
}

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
	while (av[2][i])
	{	
		if (av[2][i] < 32 || av[2][i] > 126)
		{
			if (av[2][i] < 8 || av[2][i] > 14)
				return (-1);
		}
		i++;
	}
	i = ft_atoi(av[1]);
	return (i);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	g_glob = 1;
	return ;
}

void	process(int pid, char *msg, int i)
{
	struct sigaction	wait;

	while (msg[i])
	{
		if (msg[i] == '0')
			kill(pid, SIGUSR1);
		if (msg[i] == '1')
			kill(pid, SIGUSR2);
		wait.sa_sigaction = &handler;
		if (sigemptyset(&(wait).sa_mask) == -1)
			exit(1);
		sigaddset(&(wait).sa_mask, SIGUSR1);
		wait.sa_flags = SA_SIGINFO;
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
		i++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
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
		i++;

	}
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
	process(i, msg, 0);
	ft_putstr("recu\n");
	free(msg);
}
