//
// Created by Duncan Marget on 2/8/21.
//
#include "minirt.h"
void        normal(t_mini_rt *rt, t_obj *ptr_sp)
{
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,rt->t_min));
	rt->n = sub_vec(ptr_sp->vec, rt->p);
	rt->n = vec_normalize(rt->n);
}
void normal_cy(t_mini_rt *rt,t_obj *obj)
{
	double t;
	t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head, t * 0.9999));
	rt->pc = sub_vec(obj->vec,rt->p);
	rt->n = sub_vec(multi_vec(obj->nvec,dot_vec(rt->pc,obj->nvec)),rt->pc);
	rt->n = multi_vec(vec_normalize(rt->n),-1);
	rt->vn = obj->vec;
	rt->vn_n = obj->d /2;
	obj->flag = 1;
}
int revers_normal(t_mini_rt *rt)
{
	double x = rt->tail.x - rt->vn.x;
	double y = rt->tail.y - rt->vn.y;
	double z = rt->tail.z - rt->vn.z;
	double t  = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	if(t < rt->vn_n)
		return (1);
	return(0);
}
void        normal_plane(t_mini_rt *rt, t_obj *obj)
{
	double t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.99));
	rt->n = vec_normalize(obj->nvec);
//	rt->n = obj->nvec;
}
void	find_normal(t_mini_rt *rt,t_obj *obj)
{
	if(obj->id == 2)
		normal_plane(rt,obj);
	if(obj->id == 1)
		normal(rt,obj);
	if(obj->id == 3)
		normal_plane(rt,obj);
	if(obj->id == 4)
		normal_cy(rt,obj);
	if(obj->id == 5)
		normal_plane(rt,obj);
}