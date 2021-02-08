//
// Created by Duncan Marget on 2/8/21.
//
#include "minirt.h"
t_vec	quadratic_cylinder(t_vec d, t_obj *cy, t_vec oc)
{
	t_equeal eq;
	t_vec	t;
	t_vec	h;
	t_vec	och;
	h = multi_vec(cy->nvec, dot_vec(d, cy->nvec));
	h = sub_vec(d,h);
	och = multi_vec(cy->nvec, dot_vec(oc, cy->nvec));
	och = sub_vec(oc,och);
	eq.k1 = dot_vec(h, h);
	eq.k2 = 2 * dot_vec(h, och);
	eq.k3 = dot_vec(och, och) - pow(cy->d / 2, 2);
	eq.D = pow(eq.k2, 2) - 4 * eq.k1 * eq.k3;
	if (eq.D < 0)
		return ((t_vec){INFINITY, INFINITY, 0});
	if (eq.D == 0)
		return ((t_vec){-eq.k2 / (2 * eq.k1), -eq.k2 / (2 * eq.k1), 0});
	t.x = (-eq.k2 + sqrt(eq.D)) / (2 * eq.k1);
	t.y = (-eq.k2 - sqrt(eq.D)) / (2 * eq.k1);
	return (t);
}
double			cylinder_equal(t_mini_rt *rt,t_obj *cy,t_vec o, t_vec d)
{
	t_vec t;
	t_vec p[2];
	double h[2];
	double res = INFINITY;
	t_vec oc;
	cy->nvec = vec_normalize(cy->nvec);
	oc = sub_vec(cy->vec, o);
	t = quadratic_cylinder(d, cy, oc);
	if (t.x == INFINITY && t.y == INFINITY)
		return (INFINITY);
	p[0] = sum_vec(o, multi_vec(d, t.x));
	h[0] = dot_vec(cy->nvec, sub_vec(cy->vec, p[0]));
	p[1] = sum_vec(o, multi_vec(d, t.y));
	h[1] = dot_vec(cy->nvec, sub_vec(cy->vec, p[1]));
	if (-cy->h / 2 <= h[0] && h[0] <= cy->h / 2 && t.x > 0.00001)
		res =  t.x;
	if (-cy->h / 2 <= h[1] && h[1] <= cy->h / 2 && t.y > 0.00001)
		res =  t.y;
	return(res);
}