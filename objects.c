#include "minirt.h"
//void  sphere_equal(t_mini_rt *rt, t_obj *tmp,t_vec ori,t_vec dir)
//{
//	t_equeal eq;
//
//	eq.res = sub_vec(tmp->vec, ori);
//	eq.k1 = dot_vec(dir, dir);
//	eq.k2 = 2 * dot_vec(eq.res, dir);
//	eq.k3 = dot_vec(eq.res,eq.res) - ((tmp->d/2)*(tmp->d/2));
//	eq.D = eq.k2 * eq.k2 - 4 * eq.k1 * eq.k3;
//	if (eq.D < 0)
//		rt->result = 0;
//	eq.t1 = (-eq.k2 + sqrt(eq.D)) / (2*eq.k1);
//	eq.t2 = (-eq.k2 - sqrt(eq.D)) / (2*eq.k1);
//	if(eq.t1 > eq.t2 && eq.t2 > 0)
//		rt->result = eq.t2;
//	else
//		rt->result = eq.t1;// * 0.9;
//}
double  sphere_equal(t_mini_rt *rt, t_obj *tmp,t_vec ori,t_vec dir)
{
	t_equeal eq;

	eq.res = sub_vec(tmp->vec, ori);
	eq.k1 = dot_vec(dir, dir);
	eq.k2 = 2 * dot_vec(eq.res, dir);
	eq.k3 = dot_vec(eq.res,eq.res) - ((tmp->d/2)*(tmp->d/2));
	eq.D = eq.k2 * eq.k2 - 4 * eq.k1 * eq.k3;
	if (eq.D < 0)
		return 0;
	eq.t1 = (-eq.k2 + sqrt(eq.D)) / (2*eq.k1);
	eq.t2 = (-eq.k2 - sqrt(eq.D)) / (2*eq.k1);
	if(eq.t1 > eq.t2 && eq.t2 > 0)
		return eq.t2;
	else
		return eq.t1;// * 0.9;
}
double triangle_equal(t_mini_rt *rt,t_obj *triangle,t_vec ori,t_vec dir)
{
	t_equeal eq;
	t_vec	one;
	t_vec	two;
	t_vec	t;
	t_vec	p;

	one = sub_vec(triangle->vec, triangle->nvec);
	two = sub_vec(triangle->vec, triangle->xvec);
	p = vec_cross(dir, two);
	eq.D = dot_vec(one, p);
	if (fabs(eq.D) < 0.00001)
		return (0);
	eq.k3 = 1 / eq.D;
	t = sub_vec(triangle->vec, ori);
	eq.k1 = dot_vec(t, p) * eq.k3;
	if (eq.k1 < 0 || eq.k1 > 1)
		return (0);
	t = vec_cross(t, one);
	eq.k2 = dot_vec(dir, t) * eq.k3;
	if (eq.k2 < 0 || eq.k1 + eq.k2 > 1)
		return (0);
	return (dot_vec(two, t) * eq.k3);//* 0.99;
}
//void	plane_equal(t_mini_rt *rt, t_obj *plane, t_vec ori, t_vec dir)
//{
//	t_equeal 	eq;
//
//	eq.k1 = dot_vec(sub_vec(plane->vec,ori), vec_normalize(plane->nvec));
//	eq.k2 = dot_vec(dir, vec_normalize(plane->nvec));
//	if (eq.k2 == 0 || (eq.k1 < 0 && eq.k2 < 0) || (eq.k1 > 0 && eq.k2 > 0))
//		return ;
//	eq.t1 = -eq.k1 / eq.k2;
//	if (eq.t1 < 0 || rt->result < eq.t1)
//		return ;
//	rt->result = eq.t1;//* 0.99;
//}
double plane_equal(t_mini_rt *rt, t_obj *plane, t_vec ori, t_vec dir)
{
	t_equeal 	eq;

	eq.k1 = dot_vec(sub_vec(plane->vec,ori), vec_normalize(plane->nvec));
	eq.k2 = dot_vec(dir, vec_normalize(plane->nvec));
	if (eq.k2 == 0 || (eq.k1 < 0 && eq.k2 < 0) || (eq.k1 > 0 && eq.k2 > 0))
		return (INFINITY);
	eq.t1 = -eq.k1 / eq.k2;
	if (eq.t1 < 0)
		return (INFINITY);
	return eq.t1;//* 0.99;
}
//void square_equal(t_mini_rt *rt,t_obj *square,t_vec ori,t_vec dir)
//{
//	t_equeal 	eq;
//	t_vec	d;
//
//	eq.k1 = dot_vec(sub_vec(square->vec,ori), vec_normalize(square->nvec));
//	eq.k2 = dot_vec(dir, vec_normalize(square->nvec));
//	if (eq.k2 == 0 || (eq.k1 < 0 && eq.k2 < 0) || (eq.k1 > 0 && eq.k2 > 0))
//		return ;
//	eq.t1 = eq.k1 / eq.k2 * -1.0;
//	d = sub_vec(square->vec,sum_vec(multi_vec(dir, eq.t1), ori));
//	eq.t2 = square->d / 2;
//	if (fabs(d.x) > eq.t2 || fabs(d.y) > eq.t2 || fabs(d.z) > eq.t2)
//		return ;
//	if (eq.t1 > 0)
//		rt->result = eq.t1;
//}
double square_equal(t_mini_rt *rt,t_obj *square,t_vec ori,t_vec dir)
{
	t_equeal 	eq;
	t_vec	d;

	eq.k1 = dot_vec(sub_vec(square->vec,ori), vec_normalize(square->nvec));
	eq.k2 = dot_vec(dir, vec_normalize(square->nvec));
	if (eq.k2 == 0 || (eq.k1 < 0 && eq.k2 < 0) || (eq.k1 > 0 && eq.k2 > 0))
		return (INFINITY);
	eq.t1 = eq.k1 / eq.k2 * -1.0;
	d = sub_vec(square->vec,sum_vec(multi_vec(dir, eq.t1), ori));
	eq.t2 = square->d / 2;
	if (fabs(d.x) > eq.t2 || fabs(d.y) > eq.t2 || fabs(d.z) > eq.t2)
		return (INFINITY);
	if (eq.t1 > 0)
		return eq.t1;
}
void cylindr_equal(t_mini_rt *rt,t_obj *triangle,t_vec ori,t_vec dir)
{

}