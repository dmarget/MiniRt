//
// Created by Duncan Marget on 1/16/21.
//
#include "minirt.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
//double			light_trace(t_mini_rt *rt,t_vec p,t_vec N)
//{
//	t_list  *tmp_l;
//	t_light *ptr_l;
//	double intens;
//	tmp_l = rt->list_light;
//	intens = rt->amb.range;
//	while (tmp_l)
//	{
//		ptr_l = tmp_l->content;
//		if (ptr_l)
//		{
//			if (dot_vec(N, sub_vec(p, ptr_l->vec)) > 0)
//				intens += (ptr_l->range * dot_vec(N, sub_vec(p, ptr_l->vec)))
//						  / (len_vec(N) * len_vec(sub_vec(p, ptr_l->vec)));
//		}
//		tmp_l = tmp_l->next;
//	}
//	return (intens > 1.0 ? 1.0 : intens);
//}
int angel(t_vec one,t_vec two)
{
	double ccos;
	double mdlab;
	double angel;
	mdlab = len_vec(one) * len_vec(two);
	ccos = dot_vec(one,two) / mdlab;
	angel = acos(ccos) * 180/M_PI;
	if (angel > 90)
		return (1);
	return (0);
}
void        normal(t_mini_rt *rt, t_obj *ptr_sp)
{
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,rt->t_min));
	rt->n = sub_vec(ptr_sp->vec, rt->p);
	rt->n = vec_normalize(rt->n);
	rt->n_id = 1;
}
//void		normal_cy(t_mini_rt *rt,t_obj *obj)
//{
//	t_vec	pc;
//	double	h;
//	pc = sub_vec(obj->vec,rt->p);
//	h = dot_vec(pc, obj->nvec);
//	rt->n = sub_vec(pc, multi_vec(obj->nvec, h));
//	rt->n = vec_normalize(rt->n);
//	rt->n_id = 3;
//}
void        normal_plane(t_mini_rt *rt, t_obj *obj)
{
	double t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.99));
	rt->n = vec_normalize(obj->nvec);
	rt->n = obj->nvec;
	rt->n_id = 2;
}
static t_vec	quadratic_cylinder(t_vec d, t_obj cy, t_vec oc)
{
	t_vec	t;
	t_vec	h;
	t_vec	oc_h;
	t_vec	abc;
	double	dscr;
	h = multi_vec(cy.nvec, dot_vec(d, cy.nvec));
	h = sub_vec(h,d);
	oc_h = multi_vec(cy.nvec, dot_vec(oc, cy.nvec));
	oc_h = sub_vec(oc_h,oc);
	abc.x = dot_vec(h, h);
	abc.y = 2 * dot_vec(h, oc_h);
	abc.z = dot_vec(oc_h, oc_h) - pow(cy.d / 2, 2);
	dscr = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (dscr < 0)
		return ((t_vec){INFINITY, INFINITY, 0});
	if (dscr == 0)
		return ((t_vec){-abc.y / (2 * abc.x), -abc.y / (2 * abc.x), 0});
	t.x = (-abc.y + sqrt(dscr)) / (2 * abc.x);
	t.y = (-abc.y - sqrt(dscr)) / (2 * abc.x);
	return (t);
}
double			intersect_cylinder(t_obj cy,t_vec o, t_vec d)
{
	t_vec	t;
	t_vec	p[2];
	double	h[2];
	double	res;
	t_vec	oc;
	oc = sub_vec(cy.vec,o);
	t = quadratic_cylinder(d, cy, oc);
	if (t.x == INFINITY && t.y == INFINITY)
		return (INFINITY);
	p[0] = sum_vec(o, multi_vec(d, t.x));
	h[0] = dot_vec(cy.nvec, sub_vec(cy.vec,p[0]));
	p[1] = sum_vec(o, multi_vec(d, t.y));
	h[1] = dot_vec(cy.nvec, sub_vec(cy.vec,p[1]));
	if (-cy.h / 2 <= h[0] && h[0] <= cy.h / 2 && t.x > 0.001)
		res = t.x;
	if (-cy.h / 2 <= h[1] && h[1] <= cy.h / 2 && t.y > 0.001)
		res = t.y;
	return (res);
}
void	find_normal(t_mini_rt *rt,t_obj *obj)
{
	if(obj->id == 1)
		normal(rt,obj);
	if(obj->id == 2)
		normal_plane(rt,obj);
	if(obj->id == 3)
		normal_plane(rt,obj);
//	if(obj->id == 4)
//		normal(rt,obj);
	if(obj->id == 5)
		normal_plane(rt,obj);
//	if(ibj->id == 5)
//		normal_triangular(rt,obj);
}

double 	find_objs(t_mini_rt *rt, t_obj *obj,t_vec tail,t_vec dir)
{
	double t;
	if (obj->id == 1)
		t = sphere_equal(rt, obj,tail,dir);
	if(obj->id == 2)
		t = plane_equal(rt,obj,tail,dir);
	if(obj->id == 3)
		t = square_equal(rt,obj,tail,dir);
//	if(obj->id == 4)
//		cylinder(rt,obj,tail,dir);
	if(obj->id == 5)
		t = triangle_equal(rt,obj,tail,dir);
	return (t);
}
void inter_search(t_list *tmp,double t_max,t_mini_rt *rt,t_vec cam,t_vec dir)
{
	t_obj *obj;
	double t;
	rt->t_min = INFINITY;
	rt->main = NULL;
	while (tmp)
	{
//		find_objs(rt,tmp->content,cam,dir);
		obj = tmp->content;
		obj->id == 1 ? t = sphere_equal(rt,obj,cam,dir) : 0;
		obj->id == 2 ? t = plane_equal(rt,obj,cam,dir) : 0;
		obj->id == 3 ? t = square_equal(rt,obj,cam,dir) : 0;
		obj->id == 4 ? t = intersect_cylinder(*obj,cam,dir) : 0;
		obj->id == 5 ? t = triangle_equal(rt,obj,cam,dir) : 0;
		if (t > 0.00001 && t < rt->t_min && t < t_max)
		{
			rt->t_min = t * 0.9999;
			rt->main = obj;
		}
		tmp = tmp->next;
	}
}
//t_vec			get_cy_normal(t_obj
// cy, t_vec p)
//{
//	t_vec	pc;
//	t_vec	n;
//	double	h;
//
//	pc = make_vect(p, cy.vec, '-');
//	h = dot_vec(pc, cy.nvec);
//	n = make_vect(pc, multi_vec(cy.nvec, h), '-');
//	return (normalize(n));
//}
//
//static t_vec	quadratic_cylinder(t_vec d, t_obj cy, t_vec oc)
//{
//	t_vec	t;
//	t_vec	h;
//	t_vec	oc_h;
//	t_vec	abc;
//	double	dscr;
//
//	h = multi_vec(cy.nvec, dot_vec(d, cy.nvec));
//	h = sub_vec(d, h);
//	oc_h = multi_vec(cy.nvec, dot_vec(oc, cy.nvec));
//	oc_h = sub_vec(oc, oc_h);
//	abc.x = dot_vec(h, h);
//	abc.y = 2 * dot_vec(h, oc_h);
//	abc.z = dot_vec(oc_h, oc_h) - pow(cy.d / 2, 2);
//	dscr = pow(abc.y, 2) - 4 * abc.x * abc.z;
//	if (dscr < 0)
//		return ((t_vec){INFINITY, INFINITY, 0});
//	if (dscr == 0)
//		return ((t_vec){-abc.y / (2 * abc.x), -abc.y / (2 * abc.x), 0});
//	t.x = (-abc.y + sqrt(dscr)) / (2 * abc.x);
//	t.y = (-abc.y - sqrt(dscr)) / (2 * abc.x);
//	return (t);
//}
////
//double			intersect_cylinder(t_vec o, t_vec d, t_obj cy)
//{
//	t_vec	t;
//	t_vec	p[2];
//	double	h[2];
//	double	res;
//	t_vec	oc;
//
//	oc = sub_vec(o, cy.vec);
//	t = quadratic_cylinder(d, cy, oc);
//	if (t.x == INFINITY && t.y == INFINITY)
//		return (INFINITY);
//	p[0] = sum_vec(o, multi_vec(d, t.x));
//	h[0] = dot_vec(cy.nvec, sub_vec(p[0], cy.vec));
//	p[1] = sum_vec(o, multi_vec(d, t.y));
//	h[1] = dot_vec(cy.nvec, sub_vec(p[1], cy.vec));
//	if (cy.h / 2 <= h[0] && h[0] <= cy.h / 2 && t.x > 0.001)
//		res = t.x;
//	if (cy.h / 2 <= h[1] && h[1] <= cy.h / 2 && t.y > 0.001)
//		res = t.y;
//	return (res);
//}
//Рабочий свет ----------------
t_color 			light_trace(t_list  *tmp,t_mini_rt *rt,t_vec p,t_vec N,t_obj *obj)
{
	t_list  *tmp_l;
	t_light *ptr_l;
	tmp_l = rt->list_light;
	double v_dot;
	rt->color = color_double_coe(obj->color,rt->amb.color,rt->amb.range);
	while (tmp_l)
	{
		rt->intens = 0;
		ptr_l = tmp_l->content;
		inter_search(tmp,0.99999,rt, p, sub_vec(p, ptr_l->vec));
		v_dot = dot_vec(N, sub_vec(p, ptr_l->vec));
		if(rt->main != NULL)
		{
			tmp_l = tmp_l->next;
			continue ;
		}
		if (v_dot <= 0.0 && (obj->id == 2 || obj->id == 5 || obj->id == 3))
		{
			N = multi_vec(N,-1.0);
			v_dot = dot_vec(N,sub_vec(p, ptr_l->vec));
		}
		if (v_dot > 0.0)
				rt->intens = ptr_l->range * dot_vec(N, sub_vec(p, ptr_l->vec)) /
							 (len_vec(N) * len_vec(sub_vec(p, ptr_l->vec)));
		rt->color = color_dot_coe(rt->color,ptr_l->color,rt->intens);
		tmp_l = tmp_l->next;
	}
	return (rt->color);
}
int         TraceRay(t_mini_rt *rt,t_vec cam,t_vec dir)
{
	t_list *tmp;
	tmp = rt->list_obj;
	int color;
	inter_search(tmp,INFINITY,rt, cam, dir);
	if (rt->main == NULL)
		return (0x00000000);
	find_normal(rt,rt->main);
	color = create_trgb(light_trace(tmp,rt, rt->p,rt->n,rt->main));
	return (color);
}
// -------------------
void             put_images(t_mini_rt *rt)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int x;
	int y = -rt->res.y/2;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, rt->res.x, rt->res.y, "FKMiniRT!");
	img.img = mlx_new_image(mlx, rt->res.x, rt->res.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	while (y < rt->res.y/2)
	{
		x = -rt->res.x/2;
		while (x < rt->res.x/2)
		{
			main_cam(rt);
			rt->head = cam_direction(rt,x,y);
			mlx_pixel_put(mlx, mlx_win, rt->res.x/2 + x, rt->res.y/2 - y, TraceRay(rt,rt->tail,rt->head));
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

