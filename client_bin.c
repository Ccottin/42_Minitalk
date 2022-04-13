/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:11:07 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/13 16:17:52 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

char	get_bin_char(char *c)
{
	char	ret;

	if ((*c & 1) == 1)
		ret = '1';
	else
		ret = '0';
	*c >>= 1;
	return (ret);
}

char	*get_bin(char *str)
{
	unsigned int	j;
	unsigned int	x;
	int				i;
	char			*ret;

	ret = ft_calloc((ft_strlen(str) * 8) + 2);
	if (!ret)
		return (NULL);
	x = 0;
	j = 0;
	while (str[j])
	{
		i = 7;
		while (i > -1)
		{
			ret[x + i] = get_bin_char(&(str)[j]);
			i--;
		}
		x += 8;
		j++;
	}
	return (ret);
}
