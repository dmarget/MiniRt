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

int			create_trgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

t_color		color_dot_coe(t_color color1, t_color color2, double coe)
{
	t_color	new;

	new.r = color1.r + color2.r * coe;
	new.g = color1.g + color2.g * coe;
	new.b = color1.b + color2.b * coe;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return (new);
}

t_color		color_double_coe(t_color color1, t_color color2, double coe)
{
	t_color new;

	new.r = color1.r * coe + color2.r * coe;
	new.g = color1.g * coe + color2.g * coe;
	new.b = color1.b * coe + color2.b * coe;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return (new);
}

t_color		parse_rgb(t_mini_rt *rt)
{
	t_color	color;

	color.r = ft_atoi_rt(rt->split_rgb[0], rt);
	color.g = ft_atoi_rt(rt->split_rgb[1], rt);
	color.b = ft_atoi_rt(rt->split_rgb[2], rt);
	return (color);
}
