/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:04:33 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/08 18:20:33 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	*ft_calloc(int size);
void	ft_putnbr(int n);
int		ft_strlen(char *str);
int		ft_putstr(char *str);
int		ft_atoi(char *str);
char	*ft_concat(char *s1, char *s2);

#endif
