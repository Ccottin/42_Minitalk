/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:03:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/08 18:20:07 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

void	*ft_calloc(int size)
{
	int	i;
	char	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = 0;
		i++;
	}
	return ((void*)ret);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

int	ft_putstr(char * str)
{
	int	i;
	int	ret;

	if (!str)
	{
		ret = write(1, "(null)", 6);
		return (ret);
	}
	i = ft_strlen(str);
	ret = write(1, str, i);
	return (ret);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n > 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
	else
		ft_putchar(n % 10 + 48);
}
