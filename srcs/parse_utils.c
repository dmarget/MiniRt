/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		valid_d(double *d, t_mini_rt *rt)
{
	if (*d < 0)
		error("Invalid diametr", rt);
}

void		nul_setup(t_mini_rt *rt)
{
	rt->list_cam = NULL;
	rt->list_light = NULL;
	rt->list_obj = NULL;
}

int			check_split(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_vec		parse_vec(t_mini_rt *rt)
{
	t_vec	vec;

	vec.x = ft_atof_rt(rt->line_xyz[0], rt);
	vec.y = ft_atof_rt(rt->line_xyz[1], rt);
	vec.z = ft_atof_rt(rt->line_xyz[2], rt);
	return (vec);
}

void		clear_arr(char ***str)
{
	int		i;

	i = -1;
	while ((*str)[++i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
	}
	free((*str));
	(*str) = NULL;
}
