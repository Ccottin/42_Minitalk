/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:10:05 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/13 16:21:32 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

void	ft_check(char **msg, char **str, int *j)
{
	*msg = ft_concat(*msg, *str);
	if (!*msg)
	{
		free(*str);
		exit(1);
	}
	*str = NULL;
	*j = 0;
}

int	ft_getmsg(char c)
{
	static char	*msg = NULL;
	static char	*str = NULL;
	static int	j = 0;

	if (!str)
	{
		str = ft_calloc(1001);
		if (!str)
			exit(1);
	}
	str[j] = c;
	j++;
	if (j == 999)
		ft_check(&msg, &str, &j);
	if (c == 0)
	{
		ft_check(&msg, &str, &j);
		ft_putstr(msg);
		free(msg);
		msg = NULL;
		return (1);
	}
	return (0);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t			pid = 0;
	static unsigned char	c = 0;
	static int				i = 0;

	(void)ucontext;
	if (pid == 0)
		pid = info->si_pid;
	if (info->si_pid != pid)
		reset(&pid, &i, info->si_pid);
	if (i < 8)
	{
		if (sig == SIGUSR1)
			c = c * 2;
		if (sig == SIGUSR2)
			c = c * 2 + 1;
		i++;
	}
	if (i == 8)
	{
		if (ft_getmsg(c) == 1)
			pid = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	process(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &handler;
	if (sigemptyset(&(sig).sa_mask) == -1)
		exit(1);
	sigaddset(&(sig).sa_mask, SIGUSR1);
	sigaddset(&(sig).sa_mask, SIGUSR2);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
	}
}

int	main(void)
{
	int	i;

	i = getpid();
	if (i < 2)
		exit(0);
	ft_putstr("PID : ");
	ft_putnbr(i);
	ft_putstr("\n");
	process();
	return (0);
}
