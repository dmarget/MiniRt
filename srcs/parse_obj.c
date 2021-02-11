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

void		ft_parse_pl(char *line, t_mini_rt *rt)
{
	t_obj	*pl;

	if (!(pl = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in plane", rt);
	pl->id = 2;
	rt->split_xyz = ft_split(rt->split[1], ',');
	pl->vec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	rt->split_xyz = ft_split(rt->split[2], ',');
	pl->nvec.x = ft_atof(rt->split_xyz[0]);
	pl->nvec.y = ft_atof(rt->split_xyz[1]);
	pl->nvec.z = ft_atof(rt->split_xyz[2]);
	clear_arr(&rt->split_xyz);
	check_vec(&pl->nvec.x, &pl->nvec.y, &pl->nvec.z, rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	pl->color.r = ft_atoi(rt->split_rgb[0]);
	pl->color.g = ft_atoi(rt->split_rgb[1]);
	pl->color.b = ft_atoi(rt->split_rgb[2]);
	clear_arr(&rt->split_rgb);
	check_rgb(&pl->color.r, &pl->color.r, &pl->color.r, rt);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(pl));
	clear_arr(&rt->split);
}

void		ft_parse_sp(char *line, t_mini_rt *rt)
{
	t_obj	*sp;

	if (!(sp = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in sphera", rt);
	sp->id = 1;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sp->vec.x = ft_atof_rt(rt->split_xyz[0], rt) * -1;
	sp->vec.y = ft_atof_rt(rt->split_xyz[1], rt);
	sp->vec.z = ft_atof_rt(rt->split_xyz[2], rt);
	clear_arr(&rt->split_xyz);
	sp->d = ft_atof_rt(rt->split[2], rt);
	valid_d(&sp->d, rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	sp->color.r = ft_atoi_rt(rt->split_rgb[0], rt);
	sp->color.g = ft_atoi_rt(rt->split_rgb[1], rt);
	sp->color.b = ft_atoi_rt(rt->split_rgb[2], rt);
	clear_arr(&rt->split_rgb);
	check_rgb(&sp->color.r, &sp->color.r, &sp->color.r, rt);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sp));
	clear_arr(&rt->split);
}

void		ft_parse_sq(char *line, t_mini_rt *rt)
{
	t_obj	*sq;

	if (!(sq = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 5)
		error("Invalid arguments in square", rt);
	sq->id = 3;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sq->vec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	rt->split_xyz = ft_split(rt->split[2], ',');
	sq->nvec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	check_vec(&sq->nvec.x, &sq->nvec.y, &sq->nvec.z, rt);
	sq->d = ft_atof_rt(rt->split[3], rt);
	valid_d(&sq->d, rt);
	rt->split_rgb = ft_split(rt->split[4], ',');
	sq->color.r = ft_atoi_rt(rt->split_rgb[0], rt);
	sq->color.g = ft_atoi_rt(rt->split_rgb[1], rt);
	sq->color.b = ft_atoi_rt(rt->split_rgb[2], rt);
	check_rgb(&sq->color.r, &sq->color.r, &sq->color.r, rt);
	clear_arr(&rt->split_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sq));
	clear_arr(&rt->split);
}

void		ft_parse_cy(char *line, t_mini_rt *rt)
{
	t_obj	*cy;

	if (!(cy = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 6)
		error("Invalid arguments in cylinder", rt);
	cy->id = 4;
	rt->split_xyz = ft_split(rt->split[1], ',');
	cy->vec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	rt->split_xyz = ft_split(rt->split[2], ',');
	cy->nvec = parse_vec(rt);
	check_vec(&cy->nvec.x, &cy->nvec.y, &cy->nvec.z, rt);
	clear_arr(&rt->split_xyz);
	cy->d = ft_atof_rt(rt->split[3], rt);
	valid_d(&cy->d, rt);
	cy->h = ft_atof_rt(rt->split[4], rt);
	valid_d(&cy->h, rt);
	rt->split_rgb = ft_split(rt->split[5], ',');
	cy->color = parse_rgb(rt);
	check_rgb(&cy->color.r, &cy->color.r, &cy->color.r, rt);
	clear_arr(&rt->split_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(cy));
	clear_arr(&rt->split);
}

void		ft_parse_tr(char *line, t_mini_rt *rt)
{
	t_obj	*tr;

	if (!(tr = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(", rt);
	if (check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) != 4)
		error("Invalid arguments in triangl", rt);
	tr->id = 5;
	rt->split_xyz = ft_split(rt->split[0], ',');
	tr->vec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	rt->split_xyz = ft_split(rt->split[1], ',');
	tr->nvec = parse_vec(rt);
	clear_arr(&rt->split_xyz);
	rt->split_xyz = ft_split(rt->split[2], ',');
	tr->xvec = parse_vec(rt);
	check_triangle(tr->vec, tr->nvec, tr->xvec, rt);
	clear_arr(&rt->split_xyz);
	rt->split_rgb = ft_split(rt->split[3], ',');
	tr->color.r = ft_atoi_rt(rt->split_rgb[0], rt);
	tr->color.g = ft_atoi_rt(rt->split_rgb[1], rt);
	tr->color.b = ft_atoi_rt(rt->split_rgb[2], rt);
	check_rgb(&tr->color.r, &tr->color.r, &tr->color.r, rt);
	clear_arr(&rt->split_rgb);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(tr));
	clear_arr(&rt->split);
}
