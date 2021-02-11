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

#include "minirt.h"

double		ft_atof_rt(char *str, t_mini_rt *rt)
{
	double	res1;
	double	res2;
	int		l;
	int		k;
	int		i;

	i = 0;
	k = 1;
	res1 = (double)ft_atoi_rt(str, rt);
	str[i] == '-' && res1 == 0 ? k = -1 : 0;
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	if (*str == '.')
		error("Invalid argument",rt);
	res2 = (double)ft_atoi_rt(str, rt);
	l = ft_strlen(str);
	while (l--)
		res2 /= 10;
	return ((res1 + res2) * k);
}
