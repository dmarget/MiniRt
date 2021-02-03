//
// Created by Duncan Marget on 1/10/21.
//
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 09:47:25 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/10 11:22:03 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double  ft_atof(char *str)
{
	double  res1;
	double  res2;
	int     l;
	int     k;
	int     i;

	i = 0;
	k = 1;
	res1 = (double)ft_atoi(str);
	str[i] == '-' && res1 == 0 ? k = -1 : 0;
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	res2 = (double)ft_atoi(str);
	l = ft_strlen(str);
	while (l--)
		res2 /= 10;
	return ((res1 + res2) * k);
}