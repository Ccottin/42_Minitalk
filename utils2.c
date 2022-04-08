/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:13:11 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/08 17:13:53 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

int	get_atoilen(int n)
{
	int	i;

	i = 1;
	while (n > 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n);
}

char	*ft_concat(char *s1, char *s2)
{
	int	j;
	int	i;
	char	*ret;

	if (!s1)
		return (s2);
	ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	free(s2);
	return (ret);
}
