/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
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

void	check_vec(double *x, double *y, double *z, t_mini_rt *rt)
{
	if (*x > 1 || *x < -1 || *y > 1 || *y < -1 || *z > 1 || *z < -1)
	{
		error("Invalid vector", rt);
		return ;
	}
}
