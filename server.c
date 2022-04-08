/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:10:05 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/08 18:44:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

char	ft_btoc(char *bin)
{
	int	i;
	unsigned char	c;


	i = 0;
	c = 0;
	while (i < 8)
	{
		c = c * 2 + (bin[i] - 48);
		i++;
	}
	return (c);
}

void	ft_check(char **msg, char **str, int *j)
{
	*msg = ft_concat(*msg, *str);
	if (!*msg)
	{
		free(*str);
		exit(1);
	}
	*str = NULL;
	j++;
	j = 0;
}

void	ft_getmsg(char c, int mark)
{
	static char	*msg = NULL;
	static char	*str = NULL;
	static int	j = 0;

	if (mark == 1)
	{
		ft_check(&msg, &str, &j);
		ft_putstr(msg);
		free(msg);
		return ;
	}
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
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	bin[9];
	static int	i = 0;
	(void)ucontext;
	if (sig == SIGUSR1)
		bin[i++] = '0';
	if (sig == SIGUSR2)
		bin[i++] = '1';
	if (i == 8)
	{
		ft_getmsg(ft_btoc(bin), 0);
		bin[i] = 0;
		i = 0;
	}
	if (usleep(1000000) == 0)
		ft_getmsg(0, 1);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int	i;
	struct sigaction	sig;

	i = getpid();
	if (i < 2)
		exit(0);
	ft_putstr("PID : ");
	ft_putnbr(i);
	ft_putstr("\n");
	sig.sa_sigaction = &handler;
	if (sigemptyset(&(sig).sa_mask) == -1)
		exit(1);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
	
	}
	return (0);
}
