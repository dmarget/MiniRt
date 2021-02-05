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
}
//static void	ft_init_mpn(t_rtam_cy *rt, t_cylinder *cy, double t)
//{
//	rt->m = ft_xyz_scal(rt->d, cy->normal) * t +
//			 ft_xyz_scal(rt->oc, cy->normal);
//	rt->p = ft_xyz_plus(rt->o, ft_xyz_mult_db(rt->d, t * 0.999));
//	rt->n = ft_xyz_minus(rt->p, rt->minp);
//	rt->n = ft_xyz_minus(rt->n, ft_xyz_mult_db(cy->normal, rt->m));
//	rt->n = ft_xyz_normalaze(rt->n);
//}
//void		normal_cy(t_mini_rt *rt,t_obj *obj)
//{
//	t_vec pc;
//	t_vec vm;
//	double h;
//	double t;
//	t = rt->t_min;
//	obj->nvec = vec_normalize(obj->nvec);
//	rt->p = sum_vec(rt->tail, multi_vec(rt->head, t * 0.9999));
//	pc = sub_vec(obj->vec, rt->p);
////	vm = multi_vec(obj->nvec, rt->n_id);
//	h = dot_vec(pc, obj->nvec);
////	rt->n = vec_normalize(sub_vec(vm, pc));
//	rt->n = sub_vec(pc, multi_vec(obj->nvec, h));
//}
void normal_cy(t_mini_rt *rt,t_obj *obj)
{
	t_vec pc;
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
//void	normal_cy(t_mini_rt *rt,t_obj *obj)
//{
//	t_vec ps;
//	obj->nvec = vec_normalize(obj->nvec);
//	double t = rt->t_min;
//	rt->m = dot_vec(rt->head, obj->nvec) * t +
//		dot_vec(sub_vec(obj->vec,rt->tail), obj->nvec);
//	rt->p = sum_vec(rt->tail, multi_vec(rt->head, t * 0.999));
////	rt->n = sub_vec(rt->p, rt->minp);
//	rt->n = sub_vec(multi_vec(obj->nvec, rt->m),rt->n);
//	rt->n = vec_normalize(rt->n);
//}
//void		normal_cy(t_mini_rt *rt,t_obj *obj)
//{
//	t_vec ps;
//	t_vec normal = vec_normalize(obj->nvec);
//	double t = rt->t_min;
////	rt->p = (t_vec){0.0,0.0,0.0};
//	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.9999));
//	ps = sub_vec(obj->vec,rt->p);
//	rt->n = sub_vec(multi_vec(normal,dot_vec(ps,normal)),ps);
//	rt->n = vec_normalize(rt->n);
//}
//void		normal_cy(t_mini_rt *rt,t_obj *cy)
//{
//	t_vec pc;
//	double h;
//	double t;
//	t = rt->t_min;
//	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.9999));
//	cy->nvec = vec_normalize(cy->nvec);
//	pc = sub_vec(rt->p,cy->vec);
//	h = dot_vec(pc,cy->nvec);
//	rt->n = sub_vec(multi_vec(cy->nvec,h),pc);
//}
//t_vec			get_cy_normal(t_mini_rt *rt,t_obj *cy)
//{
//	t_vec	pc;
//	t_vec	n;
//	double	h;
//	double t;
//	t = rt->t_min;
//	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.9999));
//	pc = sub_vec(cy->vec,rt->p);
//	h = dot_vec(pc, cy->nvec);
//	n = sub_vec(multi_vec(cy->nvec, h),pc);
//	return (vec_normalize(n));
//}
void        normal_plane(t_mini_rt *rt, t_obj *obj)
{
	double t = rt->t_min;
	rt->p = sum_vec(rt->tail, multi_vec(rt->head,t * 0.99));
	rt->n = vec_normalize(obj->nvec);
//	rt->n = obj->nvec;
}
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
//static t_vec	quadratic_cylinder(t_vec d, t_obj cy, t_vec oc)
//{
//	t_equeal eq;
//	t_vec	t;
//	t_vec	h;
//	t_vec	och;
//	h = multi_vec(cy.nvec, dot_vec(d, cy.nvec));
//	h = sub_vec(h,d);
//	och = multi_vec(cy.nvec, dot_vec(oc, cy.nvec));
//	och = sub_vec(och,oc);
//	eq.k1 = dot_vec(h, h);
//	eq.k2 = 2 * dot_vec(h, och);
//	eq.k3 = dot_vec(och, och) - pow(cy.d / 2, 2);
//	eq.D = pow(eq.k2, 2) - 4 * eq.k1 * eq.k3;
//	if (eq.D < 0)
//		return ((t_vec){INFINITY, INFINITY, 0});
//	if (eq.D == 0)
//		return ((t_vec){-eq.k2 / (2 * eq.k1), -eq.k2 / (2 * eq.k1), 0});
//	t.x = (-eq.k2 + sqrt(eq.D)) / (2 * eq.k1);
//	t.y = (-eq.k2 - sqrt(eq.D)) / (2 * eq.k1);
//	return (t);
//}
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
//		get_cy_normal(rt,obj);
	if(obj->id == 5)
		normal_plane(rt,obj);
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
		obj->id == 4 ? t = cylinder_equal(rt,obj,cam,dir) : 0;
		obj->id == 5 ? t = triangle_equal(rt,obj,cam,dir) : 0;
		if (t > 0.00001 && t < rt->t_min && t < t_max)
		{
			rt->t_min = t;// * 0.9999;
			rt->main = obj;
		}
		tmp = tmp->next;
	}
}
//
//static t_vec	quadratic_cylinder(t_vec d, t_obj cy, t_vec oc)
//{
//	t_vec	t;
//	t_vec	h;
//	t_vec	och;
//	t_vec	abc;
//	double	dscr;
//
//	h = multi_vec(cy.nvec, dot_vec(d, cy.nvec));
//	h = sub_vec(d, h);
//	och = multi_vec(cy.nvec, dot_vec(oc, cy.nvec));
//	och = sub_vec(oc, och);
//	abc.x = dot_vec(h, h);
//	abc.y = 2 * dot_vec(h, och);
//	abc.z = dot_vec(och, och) - pow(cy.d / 2, 2);
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
//double revers_normal(t_mini_rt *rt,t_obj *obj)
//{
//	if( )
//}
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
		inter_search(tmp,0.9999,rt, p, sub_vec(p, ptr_l->vec));
		v_dot = dot_vec(N, sub_vec(p, ptr_l->vec));
		if(rt->main != NULL)
		{
			tmp_l = tmp_l->next;
			continue ;
		}
		if (v_dot < 0.0 && (obj->id == 2 || obj->id == 5 || obj->id == 3))
		{
			N = multi_vec(N,-1.0);
			v_dot = dot_vec(N,sub_vec(p, ptr_l->vec));
		}
//		if(len_vec(rt->pc) < rt->vn_n && obj->flag == 1)
		if(obj->id == 4 && v_dot < 0)
		{
			v_dot *= -1;
			N = multi_vec(N, -1.0);
		}
//		if((obj->id == 4 ) && dot_vec(N,sub_vec(p,ptr_l->vec)) < 0)
//			if(revers_normal(rt))
//				N = multi_vec(N,-1.0);
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

