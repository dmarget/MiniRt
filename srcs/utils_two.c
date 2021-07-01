/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_id_cy(t_mini_rt *rt, t_obj *obj)
{
	if (obj->id == 4 && rt->v_dot < 0)
		rt->n = n_check(rt, rt->n);
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

void	check_arg(char **str, t_mini_rt *rt)
{
	if (check_split(str) != 3)
		error("Invalid number arg", rt);
}

t_vec	parse_nvec(t_mini_rt *rt)
{
	t_vec	vec;

	vec.x = ft_atof_rt(rt->line_xyz[0], rt);
	vec.y = ft_atof_rt(rt->line_xyz[1], rt);
	vec.z = ft_atof_rt(rt->line_xyz[2], rt);
	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		error("Invalid normal", rt);
	return (vec);
}

void	check_vec(double *x, double *y, double *z, t_mini_rt *rt)
{
	if (*x > 1 || *x < -1 || *y > 1 || *y < -1 || *z > 1 || *z < -1)
	{
		error("Invalid vector", rt);
		return ;
	}
}
