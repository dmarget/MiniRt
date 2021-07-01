/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double		dot_vec(t_vec one, t_vec two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}

t_vec		multi_vec(t_vec vec, double s)
{
	t_vec	res;

	res.x = vec.x * s;
	res.y = vec.y * s;
	res.z = vec.z * s;
	return (res);
}

t_vec		vec_normalize(t_vec v)
{
	t_vec	norm;
	double	len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}
