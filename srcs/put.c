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

void		inter_obj(double t_max, t_mini_rt *rt, t_vec cam, t_vec dir)
{
	t_obj	*obj;
	double	t;
	t_list	*tmp_t;

	tmp_t = rt->tmp_t;
	rt->t_min = INFINITY;
	rt->main = NULL;
	t = INFINITY;
	while (tmp_t)
	{
		obj = tmp_t->content;
		obj->id == 1 ? t = sphere_equal(obj, cam, dir) : 0;
		obj->id == 2 ? t = plane_equal(obj, cam, dir) : 0;
		obj->id == 3 ? t = square_equal(obj, cam, dir) : 0;
		obj->id == 4 ? t = cylinder_equal(obj, cam, dir) : 0;
		obj->id == 5 ? t = triangle_equal(obj, cam, dir) : 0;
		if (t > 0.00001 && t < rt->t_min && t < t_max)
		{
			rt->t_min = t;
			rt->main = obj;
		}
		tmp_t = tmp_t->next;
	}
}

t_color		light_trace(t_mini_rt *rt, t_vec p, t_obj *obj)
{
	t_list	*tmp_l;
	t_light	*ptr_l;

	tmp_l = rt->list_light;
	rt->color = color_double_coe(obj->color, rt->amb.color, rt->amb.range);
	while (tmp_l)
	{
		rt->intens = 0;
		ptr_l = tmp_l->content;
		inter_obj(0.9999, rt, p, sub_vec(p, ptr_l->vec));
		rt->v_dot = dot_vec(rt->n, sub_vec(p, ptr_l->vec));
		if (rt->main != NULL)
		{
			tmp_l = tmp_l->next;
			continue ;
		}
		if (rt->v_dot < 0.0 && (obj->id == 2 || obj->id == 5 || obj->id == 3))
			rt->n = nv_check(rt, rt->n, p, ptr_l);
		check_id_cy(rt, obj);
		rt->v_dot > 0.0 ? rt->intens = ptr_l->range * dot_vec(rt->n, sub_vec(p,\
		ptr_l->vec)) / (len_vec(rt->n) * len_vec(sub_vec(p, ptr_l->vec))) : 0;
		rt->color = color_dot_coe(rt->color, ptr_l->color, rt->intens);
		tmp_l = tmp_l->next;
	}
	return (rt->color);
}
int			traceray(t_mini_rt *rt, t_vec cam, t_vec dir)
{
	t_list	*tmp;
	int		color;

	tmp = rt->list_obj;
	rt->tmp_t = tmp;
	inter_obj(INFINITY, rt, cam, dir);
	if (rt->main == NULL)
		return (0x00000000);
	find_normal(rt, rt->main);
	color = create_trgb(light_trace(rt, rt->p, rt->main));
	return (color);
}

void		render(t_mini_rt *rt)
{
	int		x;
	int		y;

	y = -rt->res.y / 2;
	rt->img.img = mlx_new_image(rt->mlx, rt->res.x, rt->res.y);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,\
	&rt->img.line_length, &rt->img.endian);
	while (++y < rt->res.y / 2 - 1)
	{
		x = -rt->res.x / 2;
		while (++x < rt->res.x / 2 - 1)
		{
			rt->head = cam_direction(rt, x, y);
			my_mlx_pixel_put(&rt->img, rt->res.x / 2 + x, rt->res.y / 2 - y,\
			traceray(rt, rt->tail, rt->head));
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
}

void		images_main(t_mini_rt *rt)
{
	rt->tmp = rt->list_cam;
	main_cam(rt);
	rt->mlx = mlx_init();
	rt->win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "FKMiniRT!");
	render(rt);
	if (rt->flag == 1)
		save(rt);
	mlx_hook(rt->win, 2, 0, ft_close, rt);
	mlx_hook(rt->win, 2, 0, ft_close, rt);
	mlx_hook(rt->win, 17, 0, ft_exit, rt);
	mlx_loop(rt->mlx);
}
