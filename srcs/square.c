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

static	t_vec	get_vo(t_obj *sq, t_vec up, t_vec right, int flag)
{
	t_vec		p;

	p = sum_vec(sq->vec, sum_vec(multi_vec(up, sq->d * flag / 2),\
	multi_vec(right, sq->d * flag / 2)));
	return (p);
}

static	t_vec	get_vs(t_obj *sq, t_vec up, t_vec right, int flag)
{
	t_vec		p;

	p = sum_vec(sq->vec, sum_vec(multi_vec(up, sq->d * flag / 2),\
	multi_vec(right, -sq->d * flag / 2)));
	return (p);
}

static	t_vec	new_vec(double x, double y, double z)
{
	t_vec		new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

static	t_obj	get_vector(t_vec ray, t_obj *sq)
{
	t_obj		tr;
	t_vec		normal;
	t_vec		sky;
	t_vec		right;
	t_vec		up;


	normal = vec_normalize(sq->nvec);
	if (0 > (dot_vec(sq->nvec, ray)))
		normal = multi_vec(sq->nvec, -1);
	sky = (fabs(normal.z) != 1) ? new_vec(0, 0, 1) : new_vec(0, 1, 0);
	right = vec_normalize(vec_cross(normal, sky));
	up = vec_cross(right, normal);
	tr.vec = get_vo(sq, up, right, 1);
	tr.svec = get_vs(sq, up, right, -1);
	tr.xvec = get_vs(sq, up, right, 1);
	tr.nvec = get_vo(sq, up, right, -1);
	return (tr);
}

//double square_equal(t_obj *square,t_vec ori,t_vec dir)
//{
//	t_equeal 	eq;
//	t_vec	d;
//
//	eq.k1 = dot_vec(sub_vec(square->vec,ori), vec_normalize(square->nvec));
//	eq.k2 = dot_vec(dir, vec_normalize(square->nvec));
//	if (eq.k2 == 0 || (eq.k1 < 0 && eq.k2 < 0) || (eq.k1 > 0 && eq.k2 > 0))
//		return (INFINITY);
//	eq.t1 = eq.k1 / eq.k2 * -1.0;
//	d = sub_vec(square->vec,sum_vec(multi_vec(dir, eq.t1), ori));
//	eq.t2 = square->d / 2;
//	if (fabs(d.x) > eq.t2 || fabs(d.y) > eq.t2 || fabs(d.z) > eq.t2)
//		return (INFINITY);
//	if (eq.t1 > 0)
//		return eq.t1;
//}
double			square_equal(t_obj *square, t_vec ori, t_vec dir)
{
	t_equeal	eq;
	t_obj		tr;
	t_vec		hit_vec;
	t_vec		tr_ori;
	t_vec		tr_dir;

	eq.k1 = plane_equal(square, ori, dir);
	if (eq.k1 != INFINITY)
	{
		tr = get_vector(dir, square);
		tr_ori = sub_vec(tr.vec, tr.svec);
		tr_dir = sub_vec(tr.vec, tr.xvec);
		hit_vec = sub_vec(tr.vec, sum_vec(ori, multi_vec(dir, eq.k1)));
		eq.t1 = dot_vec(vec_normalize(tr_ori), hit_vec);
		eq.t2 = dot_vec(vec_normalize(tr_dir), hit_vec);
		if (0.0 <= eq.t1 && eq.t1 <= len_vec(tr_ori) &&
			0.0 <= eq.t2 && eq.t2 <= len_vec(tr_dir))
			return (eq.t1 > eq.t2 ? eq.t2 : eq.t1);
	}
	return (INFINITY);
}
