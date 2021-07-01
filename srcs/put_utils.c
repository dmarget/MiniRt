/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_close(int keycode, t_mini_rt *rt)
{
	if (keycode == 53)
	{
		mlx_destroy_window(rt->mlx, rt->win);
		exit(0);
	}
	else if (keycode == 48)
		ft_change_cam(rt);
	return (0);
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int			ft_exit(t_mini_rt *rt)
{
	mlx_destroy_window(rt->mlx, rt->win);
	exit(0);
}

t_vec		n_check(t_mini_rt *rt, t_vec n)
{
	rt->v_dot *= -1;
	n = multi_vec(n, -1.0);
	return (n);
}

t_vec		nv_check(t_mini_rt *rt, t_vec n, t_vec p, t_light *ptr_l)
{
	n = multi_vec(n, -1.0);
	rt->v_dot = dot_vec(n, sub_vec(p, ptr_l->vec));
	return (n);
}
