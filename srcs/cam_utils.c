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

void		main_cam(t_mini_rt *rt)
{
	t_cam	*ptr_cam;

	rt->main_c = rt->list_cam;
	ptr_cam = rt->main_c->content;
	rt->tail = ptr_cam->vec;
	rt->dir = ptr_cam->nvec;
	rt->fov = ptr_cam->fov;
	return ;
}

void		check_cam(t_mini_rt *rt)
{
	t_list	*tmp;

	tmp = rt->list_cam;
	if (tmp == NULL)
		error("No cam's", rt);
}

void		ft_change_cam(t_mini_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->win);
	if (rt->list_cam->next == NULL)
		rt->list_cam = rt->tmp;
	else
		rt->list_cam = rt->list_cam->next;
	rt->main_c = rt->list_cam->content;
	main_cam(rt);
	render(rt);
}

t_vec		vector(double x, double y, int w, int h)
{
	t_vec	v;

	v.x = x / w;
	v.y = y / h;
	v.z = 1;
	return (v);
}

t_vec		cam_direction(t_mini_rt *rt, double x, double y)
{
	t_vec	cam_right;
	t_vec	cam_up;
	t_vec	d;
	t_vec	v;
	double	fov;

	rt->dir = vec_normalize(rt->dir);
	fov = 2 * tan(rt->fov / 2 * M_PI / 180);
	x *= fov;
	y *= fov;
	v = vector(x, y, rt->res.x, rt->res.y);
	cam_right = vec_cross((t_vec){0.0, 1.0, 0.0}, rt->dir);
	cam_up = vec_cross(rt->dir, cam_right);
	d = dot_matrix(cam_right, cam_up, rt->dir, v);
	return (d);
}
