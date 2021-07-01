/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_parse_pl(char *line, t_mini_rt *rt)
{
	t_obj	*pl;

	if (!(pl = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ssplit_rt(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in plane", rt);
	pl->id = 2;
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	pl->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[2], ',', rt)), rt);
	pl->nvec = parse_nvec(rt);
	clear_arr(&rt->line_xyz);
	check_vec(&pl->nvec.x, &pl->nvec.y, &pl->nvec.z, rt);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[3], ',', rt)), rt);
	pl->color.r = ft_atoi(rt->line_rgb[0]);
	pl->color.g = ft_atoi(rt->line_rgb[1]);
	pl->color.b = ft_atoi(rt->line_rgb[2]);
	clear_arr(&rt->line_rgb);
	check_rgb(&pl->color.r, &pl->color.r, &pl->color.r, rt);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(pl));
	clear_arr(&rt->split);
}

void		ft_parse_sp(char *line, t_mini_rt *rt)
{
	t_obj	*sp;

	if (!(sp = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ssplit_rt(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in sphera", rt);
	sp->id = 1;
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	sp->vec.x = ft_atof_rt(rt->line_xyz[0], rt) * -1;
	sp->vec.y = ft_atof_rt(rt->line_xyz[1], rt);
	sp->vec.z = ft_atof_rt(rt->line_xyz[2], rt);
	clear_arr(&rt->line_xyz);
	sp->d = ft_atof_rt(rt->split[2], rt);
	valid_d(&sp->d, rt);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[3], ',', rt)), rt);
	sp->color.r = ft_atoi_rt(rt->line_rgb[0], rt);
	sp->color.g = ft_atoi_rt(rt->line_rgb[1], rt);
	sp->color.b = ft_atoi_rt(rt->line_rgb[2], rt);
	clear_arr(&rt->line_rgb);
	check_rgb(&sp->color.r, &sp->color.r, &sp->color.r, rt);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sp));
	clear_arr(&rt->split);
}

void		ft_parse_sq(char *line, t_mini_rt *rt)
{
	t_obj	*sq;

	if (!(sq = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ssplit_rt(&line[rt->i], " /t/n/r/v/f")) != 5)
		error("Invalid arguments in square", rt);
	sq->id = 3;
	rt->line_xyz = ft_split_rt(rt->split[1], ',', rt);
	sq->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[2], ',', rt)), rt);
	sq->nvec = parse_nvec(rt);
	clear_arr(&rt->line_xyz);
	check_vec(&sq->nvec.x, &sq->nvec.y, &sq->nvec.z, rt);
	sq->d = ft_atof_rt(rt->split[3], rt);
	valid_d(&sq->d, rt);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[4], ',', rt)), rt);
	sq->color.r = ft_atoi_rt(rt->line_rgb[0], rt);
	sq->color.g = ft_atoi_rt(rt->line_rgb[1], rt);
	sq->color.b = ft_atoi_rt(rt->line_rgb[2], rt);
	check_rgb(&sq->color.r, &sq->color.r, &sq->color.r, rt);
	clear_arr(&rt->line_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sq));
	clear_arr(&rt->split);
}

void		ft_parse_cy(char *line, t_mini_rt *rt)
{
	t_obj	*cy;

	if (!(cy = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ssplit_rt(&line[rt->i], " /t/n/r/v/f")) != 6)
		error("Invalid arguments in cylinder", rt);
	cy->id = 4;
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	cy->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[2], ',', rt)), rt);
	cy->nvec = parse_nvec(rt);
	check_vec(&cy->nvec.x, &cy->nvec.y, &cy->nvec.z, rt);
	clear_arr(&rt->line_xyz);
	cy->d = ft_atof_rt(rt->split[3], rt);
	valid_d(&cy->d, rt);
	cy->h = ft_atof_rt(rt->split[4], rt);
	valid_d(&cy->h, rt);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[5], ',', rt)), rt);
	cy->color = parse_rgb(rt);
	check_rgb(&cy->color.r, &cy->color.r, &cy->color.r, rt);
	clear_arr(&rt->line_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(cy));
	clear_arr(&rt->split);
}

void		ft_parse_tr(char *line, t_mini_rt *rt)
{
	t_obj	*tr;

	if (!(tr = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ssplit_rt(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in triangl", rt);
	tr->id = 5;
	check_arg((rt->line_xyz = ft_split_rt(rt->split[0], ',', rt)), rt);
	tr->vec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[1], ',', rt)), rt);
	tr->nvec = parse_vec(rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_xyz = ft_split_rt(rt->split[2], ',', rt)), rt);
	tr->xvec = parse_vec(rt);
	check_triangle(tr->vec, tr->nvec, tr->xvec, rt);
	clear_arr(&rt->line_xyz);
	check_arg((rt->line_rgb = ft_split_rt(rt->split[3], ',', rt)), rt);
	tr->color.r = ft_atoi_rt(rt->line_rgb[0], rt);
	tr->color.g = ft_atoi_rt(rt->line_rgb[1], rt);
	tr->color.b = ft_atoi_rt(rt->line_rgb[2], rt);
	check_rgb(&tr->color.r, &tr->color.r, &tr->color.r, rt);
	clear_arr(&rt->line_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(tr));
	clear_arr(&rt->split);
}
