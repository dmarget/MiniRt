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
#include <math.h>

t_vec		sum_vec(t_vec one, t_vec two)
{
	t_vec	res;

	res.x = one.x + two.x;
	res.y = one.y + two.y;
	res.z = one.z + two.z;
	return (res);
}

t_vec		dot_matrix(t_vec r, t_vec u, t_vec n, t_vec d)
{
	t_vec	res;

	res.x = r.x * d.x + r.y * d.y + r.z * d.z;
	res.y = u.x * d.x + u.y * d.y + u.z * d.z;
	res.z = n.x * d.x + n.y * d.y + n.z * d.z;
	return (res);
}

double		len_vec(t_vec vec)
{
	return (sqrt(dot_vec(vec, vec)));
}

t_vec		sub_vec(t_vec one, t_vec two)
{
	t_vec	res;

	res.x = two.x - one.x;
	res.y = two.y - one.y;
	res.z = two.z - one.z;
	return (res);
}

t_vec		vec_cross(t_vec one, t_vec two)
{
	t_vec	v;

	v.x = one.y * two.z - one.z * two.y;
	v.y = one.z * two.x - one.x * two.z;
	v.z = one.x * two.y - one.y * two.x;
	return (v);
}
