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

void		normal(t_mini_rt *rt, t_obj *ptr_sp)
{
	rt->p = sum_vec(rt->tail, multi_vec(rt->head, rt->t_min));
	rt->n = sub_vec(ptr_sp->vec, rt->p);
	rt->n = vec_normalize(rt->n);
}

void        normal_tr(t_mini_rt *rt, t_obj *obj)
{
	double  t;

	t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.9999));
	rt->n = vec_cross(sub_vec(obj->vec, obj->nvec), sub_vec(obj->vec, obj->xvec));
	rt->n = vec_normalize(rt->n);
}

void		normal_cy(t_mini_rt *rt, t_obj *obj)
{
	double	t;

	t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head, t * 0.9999));
	rt->pc = sub_vec(obj->vec, rt->p);
	rt->n = sub_vec(multi_vec(obj->nvec, dot_vec(rt->pc, obj->nvec)), rt->pc);
	rt->n = multi_vec(vec_normalize(rt->n), -1);
	rt->vn = obj->vec;
	rt->vn_n = obj->d / 2;
}

void		normal_plane(t_mini_rt *rt, t_obj *obj)
{
	double t;

	t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head, t * 0.99));
	rt->n = vec_normalize(obj->nvec);
}

void		find_normal(t_mini_rt *rt, t_obj *obj)
{
	if (obj->id == 2)
		normal_plane(rt, obj);
	if (obj->id == 1)
		normal(rt, obj);
	if (obj->id == 3)
		normal_plane(rt, obj);
	if (obj->id == 4)
		normal_cy(rt, obj);
	if (obj->id == 5)
		normal_tr(rt, obj);
}
