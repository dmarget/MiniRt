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

void		ft_parse_res(char *line, t_mini_rt *rt)
{
	int		w;
	int		h;

	if (*line == '\0')
		return ;
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 3)
		error("Invalid number argument in resolution", rt);
	if (ft_strlen(rt->split[1]) > 1 && ft_atoi_rt(rt->split[1], rt) < 1)
		error("You invalid", rt);
	rt->res.x = ft_atoi_rt(rt->split[1], rt);
	rt->res.y = ft_atoi_rt(rt->split[2], rt);
	if ((rt->res.x > 16384 ||  rt->res.y > 16384) && rt->flag == 1)
		error("validateTextureDimensions:1084: failed assertion `MTLTextureDescriptor has height (30000) greater"
			  " than the maximum allowed size of 16384.'", rt);
	if(rt->flag == 0)
	{
		mlx_get_screen_size(rt->mlx, &w, &h);
		rt->res.x > w ? rt->res.x = w : 0;
		rt->res.y > h ? rt->res.y = h : 0;
	}
	rt->res.x > w ? rt->res.x = w : 0;
	rt->res.y > h ? rt->res.y = h : 0;
	rt->res.flag = 1;
	if (rt->res.x < 1 || rt->res.y < 1)
		error("Resolution < 0", rt);
	clear_arr(&rt->split);
}

void		ft_parse_amb(char *line, t_mini_rt *rt)
{
	if (*line == '\0')
		return ;
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 3)
		error("Invalid arguments in ambient", rt);
	rt->amb.range = ft_atof_rt(rt->split[1], rt);
	if (rt->amb.range < 0 || rt->amb.range > 1)
		error("Invalid range ambient", rt);
	rt->line_rgb = ft_split_rt(rt->split[2], ',', rt);
	rt->amb.color.r = ft_atoi_rt(rt->line_rgb[0], rt);
	rt->amb.color.g = ft_atoi_rt(rt->line_rgb[1], rt);
	rt->amb.color.b = ft_atoi_rt(rt->line_rgb[2], rt);
	rt->amb.flag = 1;
	check_rgb(&rt->amb.color.r, &rt->amb.color.g, &rt->amb.color.b, rt);
	clear_arr(&rt->line_rgb);
	clear_arr(&rt->split);
}

void		ft_parse_cam(char *line, t_mini_rt *rt)
{
	t_cam	*tmp;

	if (!(tmp = malloc(sizeof(t_cam))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in cam", rt);
	if (*line == '\0')
		return ;
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	tmp->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[2], ',', rt)), rt);
	tmp->nvec = parse_nvec(rt);
	clear_arr(&rt->line_xyz);
	check_vec(&tmp->nvec.x, &tmp->nvec.y, &tmp->nvec.z, rt);
	tmp->fov = ft_atoi_rt(rt->split[3], rt);
	if (tmp->fov < 1 || tmp->fov > 180)
		error("Invalid fov", rt);
	ft_lstadd_back(&rt->list_cam, ft_lstnew(tmp));
	clear_arr(&rt->split);
}

void		ft_parse_light(char *line, t_mini_rt *rt)
{
	t_light	*tmp;

	if (!(tmp = malloc(sizeof(t_light))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in light", rt);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	tmp->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	tmp->range = ft_atof_rt(rt->split[2], rt);
	if (tmp->range > 1 || tmp->range < -1)
		error("Invalid light range", rt);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[3], ',', rt)), rt);
	tmp->color.r = ft_atoi_rt(rt->line_rgb[0], rt);
	tmp->color.g = ft_atoi_rt(rt->line_rgb[1], rt);
	tmp->color.b = ft_atoi_rt(rt->line_rgb[2], rt);
	clear_arr(&rt->line_rgb);
	check_rgb(&tmp->color.r, &tmp->color.r, &tmp->color.r, rt);
	ft_lstadd_back(&rt->list_light, ft_lstnew(tmp));
	clear_arr(&rt->split);
}

void		ft_parser_rt(char *line, t_mini_rt *rt)
{
	rt->i = 0;
	if (line[rt->i] == 'R')
		ft_parse_res(line, rt);
	else if (line[rt->i] == 'A')
		ft_parse_amb(line, rt);
	else if (line[rt->i] == 'c' && line[rt->i + 1] != 'y')
		ft_parse_cam(line, rt);
	else if (line[rt->i] == 'l' && line[rt->i - 1] != 'p')
		ft_parse_light(line, rt);
	else if (line[rt->i] == 'p' && line[rt->i + 1] == 'l')
		ft_parse_pl(line, rt);
	else if (line[rt->i] == 's' && line[rt->i + 1] == 'p')
		ft_parse_sp(line, rt);
	else if (line[rt->i] == 's' && line[rt->i + 1] == 'q')
		ft_parse_sq(line, rt);
	else if (line[rt->i] == 'c' && line[rt->i + 1] == 'y')
		ft_parse_cy(line, rt);
	else if (line[rt->i] == 't' && line[rt->i + 1] == 'r')
		ft_parse_tr(line, rt);
	else if (ft_strlen(line) == 0)
		return ;
	else
		error("Invalid argument", rt);
}
