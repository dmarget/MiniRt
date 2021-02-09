//
// Created by Duncan Marget on 1/16/21.
//
#include "minirt.h"

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
void inter_search(t_list *tmp,double t_max,t_mini_rt *rt,t_vec cam,t_vec dir)
{
	t_obj *obj;
	double t;
	rt->t_min = INFINITY;
	rt->main = NULL;
	while (tmp)
	{
		obj = tmp->content;
		obj->id == 1 ? t = sphere_equal(obj,cam,dir) : 0;
		obj->id == 2 ? t = plane_equal(obj,cam,dir) : 0;
		obj->id == 3 ? t = square_equal(obj,cam,dir) : 0;
		obj->id == 4 ? t = cylinder_equal(obj,cam,dir) : 0;
		obj->id == 5 ? t = triangle_equal(obj,cam,dir) : 0;
		if (t > 0.00001 && t < rt->t_min && t < t_max)
		{
			rt->t_min = t;
			rt->main = obj;
		}
		tmp = tmp->next;
	}
}
t_vec n_check(t_mini_rt *rt, t_vec n)
{
	rt->v_dot *= -1;
	n = multi_vec(n, -1.0);
	return (n);
}
t_vec nv_check(t_mini_rt *rt,t_vec n,t_vec p,t_light *ptr_l)
{
	n = multi_vec(n,-1.0);
	rt->v_dot = dot_vec(n,sub_vec(p, ptr_l->vec));
	return (n);
}
t_color 			light_trace(t_list  *tmp,t_mini_rt *rt,t_vec p,t_vec N,t_obj *obj)
{
	t_list  *tmp_l;
	t_light *ptr_l;

	tmp_l = rt->list_light;
	rt->color = color_double_coe(obj->color,rt->amb.color,rt->amb.range);
	while (tmp_l)
	{
		rt->intens = 0;
		ptr_l = tmp_l->content;
		inter_search(tmp,0.9999,rt, p, sub_vec(p, ptr_l->vec));
		rt->v_dot = dot_vec(N, sub_vec(p, ptr_l->vec));
		if(rt->main != NULL)
		{
			tmp_l = tmp_l->next;
			continue ;
		}
		if (rt->v_dot < 0.0 && (obj->id == 2 || obj->id == 5 || obj->id == 3))
			N = nv_check(rt,N,p,ptr_l);
		if(obj->id == 4 && rt->v_dot < 0)
			N = n_check(rt,N);
		rt->v_dot > 0.0 ? rt->intens = ptr_l->range * dot_vec(N, sub_vec(p, ptr_l->vec)) /
									   (len_vec(N) * len_vec(sub_vec(p, ptr_l->vec))) : 0;
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
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void render(t_mini_rt *rt)
{
	int x;
	int y = -rt->res.y/2;
	rt->img.img = mlx_new_image(rt->mlx, rt->res.x, rt->res.y);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel, &rt->img.line_length,&rt->img.endian);
	while (++y < rt->res.y/2 - 1)
	{
		x = -rt->res.x/2;
		while (++x < rt->res.x/2 - 1)
		{
			rt->head = cam_direction(rt,x,y);
			my_mlx_pixel_put(&rt->img, rt->res.x/2 + x, rt->res.y/2 - y, TraceRay(rt,rt->tail,rt->head));
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
}
int             ft_close(int keycode, t_mini_rt *rt)
{
	if(keycode == 53)
	{
		mlx_destroy_window(rt->mlx, rt->win);
		exit(0);
	}
	else if(keycode == 48)
		ft_change_cam(rt);
	return(0);
}
int ft_exit(void)
{
	exit(0);
}
void             put_images(t_mini_rt *rt)
{
	rt->tmp = rt->list_cam;
	main_cam(rt);
	rt->mlx = mlx_init();
	rt->win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "FKMiniRT!");
	render(rt);
	if(rt->flag == 1)
		save(rt);
	mlx_hook(rt->win, 2, 0, ft_close, rt);
	mlx_hook(rt->win, 2, 0,	ft_close, rt);
	mlx_hook(rt->win, 17, 0, ft_exit, rt);
	mlx_loop(rt->mlx);
}

