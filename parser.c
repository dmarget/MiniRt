//
// Created by Duncan Marget on 1/7/21.
//
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
#include "get_next_line.h"
//#include "ft_printf.h"

//              ПАРСИМ РАЗРЕШЕНИЕ
	void        ft_parse_res(char *line, t_mini_rt *rt)
{
		if(*line == '\0')
			return ;
		if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=3)
			error("Invalid number argument in resolution",rt);
		rt->res.x = ft_atoi(rt->split[1]);
		rt->res.y = ft_atoi(rt->split[2]);
		rt->res.x > 2560 ? rt->res.x = 2560 : 0;
		rt->res.y > 1440 ? rt->res.y = 1395 : 0;
		rt->res.flag += 1;
		if(rt->res.x < 1 || rt->res.y < 1)
			error("Resolution < 0",rt);
}
//              ПАРСИМ ОСВЕЩЕНИЕ
void            ft_parse_amb(char *line, t_mini_rt *rt)
{
	if(*line == '\0')
		return ;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=3)
		error("Invalid arguments in ambient",rt);
	rt->amb.range = ft_atof(rt->split[1]);
	if(rt->amb.range < 0 || rt->amb.range > 1)
		error("Invalid range ambient",rt);
	rt->split_rgb = ft_split(rt->split[2], ',');
	rt->amb.color.r = ft_atoi(rt->split_rgb[0]);
	rt->amb.color.g = ft_atoi(rt->split_rgb[1]);
	rt->amb.color.b = ft_atoi(rt->split_rgb[2]);
	rt->amb.flag += 1;
	check_rgb(&rt->amb.color.r,&rt->amb.color.g,&rt->amb.color.b);
}
// 				ПАРСИМ КАМЕРЫ
void			ft_parse_cam(char *line, t_mini_rt *rt)
{
	t_cam  *tmp;
	if(!(tmp = malloc(sizeof(t_cam))))
		error("Malloc is dead,you kill him(",rt);
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		error("Invalid arguments in cam",rt);
	if(*line == '\0')
		return ;
	rt->split_xyz = ft_split(rt->split[1], ',');
	tmp->vec.x = ft_atof(rt->split_xyz[0]);
	tmp->vec.y = ft_atof(rt->split_xyz[1]);
	tmp->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	tmp->nvec.x = ft_atof(rt->split_xyz[0]);
	tmp->nvec.y = ft_atof(rt->split_xyz[1]);
	tmp->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&tmp->nvec.x,&tmp->nvec.y,&tmp->nvec.z,rt);
	tmp->FOV = ft_atoi(rt->split[3]);
	if(tmp->FOV < 1 || tmp->FOV >= 180)
		error("Invalid fov",rt);
	tmp->flag = 1;
	ft_lstadd_back(&rt->list_cam, ft_lstnew(tmp));
}
//				Парсим свет
void      		ft_parse_light(char *line, t_mini_rt *rt)
{
	t_light   *tmp;
	if(!(tmp = malloc(sizeof(t_light))))
		error("Malloc is dead,you kill him(",rt);
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f	")) !=4)
		error("Invalid arguments in light",rt);
	rt->split_xyz = ft_split(rt->split[1], ',');
	tmp->vec.x = ft_atof(rt->split_xyz[0]);
	tmp->vec.y = ft_atof(rt->split_xyz[1]);
	tmp->vec.z = ft_atof(rt->split_xyz[2]);
	tmp->range = ft_atof(rt->split[2]);
	if(tmp->range > 1 || tmp->range < -1)
		error("Invalid light range",rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	tmp->color.r = ft_atoi(rt->split_rgb[0]);
	tmp->color.g = ft_atoi(rt->split_rgb[1]);
	tmp->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&tmp->color.r,&tmp->color.r,&tmp->color.r);
	ft_lstadd_back(&rt->list_light, ft_lstnew(tmp));
}
//				Парсим плоскость
void 			ft_parse_pl(char *line, t_mini_rt *rt)
{
	t_obj   *pl;
	if(!(pl = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(",rt);;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		error("Invalid arguments in plane",rt);
	pl->id = 2;
	rt->split_xyz = ft_split(rt->split[1], ',');
	pl->vec.x = ft_atof(rt->split_xyz[0]);
	pl->vec.y = ft_atof(rt->split_xyz[1]);
	pl->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	pl->nvec.x = ft_atof(rt->split_xyz[0]);
	pl->nvec.y = ft_atof(rt->split_xyz[1]);
	pl->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&pl->nvec.x,&pl->nvec.y,&pl->nvec.z,rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	pl->color.r = ft_atoi(rt->split_rgb[0]);
	pl->color.g = ft_atoi(rt->split_rgb[1]);
	pl->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&pl->color.r,&pl->color.r,&pl->color.r);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(pl));
}
//				Парсим сферу
void 			ft_parse_sp(char *line, t_mini_rt *rt)
{
	t_obj  *sp;
	if(!(sp = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(",rt);;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		error("Invalid arguments in sphera",rt);
	sp->id = 1;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sp->vec.x = ft_atof(rt->split_xyz[0]) * -1;
	sp->vec.y = ft_atof(rt->split_xyz[1]);
	sp->vec.z = ft_atof(rt->split_xyz[2]);
	sp->d = ft_atof(rt->split[2]);
	valid_d(&sp->d,rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	sp->color.r = ft_atoi(rt->split_rgb[0]);
	sp->color.g = ft_atoi(rt->split_rgb[1]);
	sp->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&sp->color.r,&sp->color.r,&sp->color.r);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sp));
}
//				Парсим квадрат
void 			ft_parse_sq(char *line, t_mini_rt *rt)
{
	t_obj   *sq;
	if(!(sq = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(",rt);;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=5)
		error("Invalid arguments in square",rt);
	sq->id = 3;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sq->vec.x = ft_atof(rt->split_xyz[0]);
	sq->vec.y = ft_atof(rt->split_xyz[1]);
	sq->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	sq->nvec.x = ft_atof(rt->split_xyz[0]);
	sq->nvec.y = ft_atof(rt->split_xyz[1]);
	sq->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&sq->nvec.x,&sq->nvec.y,&sq->nvec.z,rt);
	sq->d = ft_atof(rt->split[3]);
	valid_d(&sq->d,rt);
	rt->split_rgb = ft_split(rt->split[4], ',');
	sq->color.r = ft_atoi(rt->split_rgb[0]);
	sq->color.g = ft_atoi(rt->split_rgb[1]);
	sq->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&sq->color.r,&sq->color.r,&sq->color.r);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(sq));
}
//				Парсим цилиндр
void  			ft_parse_cy(char *line, t_mini_rt *rt)
{
	t_obj   *cy;
	if(!(cy = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(",rt);;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=6)
		error("Invalid arguments in cylinder",rt);
	cy->id = 4;
	rt->split_xyz = ft_split(rt->split[1], ',');
	cy->vec.x = ft_atof(rt->split_xyz[0]);
	cy->vec.y = ft_atof(rt->split_xyz[1]);
	cy->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	cy->nvec.x = ft_atof(rt->split_xyz[0]);
	cy->nvec.y = ft_atof(rt->split_xyz[1]);
	cy->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&cy->nvec.x, &cy->nvec.y, &cy->nvec.z,rt);
	cy->d = ft_atof(rt->split[3]);
	valid_d(&cy->d,rt);
	cy->h = ft_atof(rt->split[4]);
	valid_d(&cy->h,rt);
	rt->split_rgb = ft_split(rt->split[5], ',');
	cy->color.r = ft_atoi(rt->split_rgb[0]);
	cy->color.g = ft_atoi(rt->split_rgb[1]);
	cy->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&cy->color.r, &cy->color.r, &cy->color.r);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(cy));
}
//				Парсим треугольник
void  			ft_parse_tr(char *line, t_mini_rt *rt)
{
	t_obj   *tr;
	if(!(tr = malloc(sizeof(t_obj))))
		error("Malloc is dead,you kill him(",rt);
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		error("Invalid arguments in triangl",rt);
	tr->id = 5;
	rt->split_xyz = ft_split(rt->split[0], ',');
	tr->vec.x = ft_atof(rt->split_xyz[0]);
	tr->vec.y = ft_atof(rt->split_xyz[1]);
	tr->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[1], ',');
	tr->nvec.x = ft_atof(rt->split_xyz[0]);
	tr->nvec.y = ft_atof(rt->split_xyz[1]);
	tr->nvec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	tr->xvec.x = ft_atof(rt->split_xyz[0]);
	tr->xvec.y = ft_atof(rt->split_xyz[1]);
	tr->xvec.z = ft_atof(rt->split_xyz[2]);
	check_triangle(tr->vec, tr->nvec, tr->xvec,rt);
	rt->split_rgb = ft_split(rt->split[3], ',');
	tr->color.r = ft_atoi(rt->split_rgb[0]);
	tr->color.g = ft_atoi(rt->split_rgb[1]);
	tr->color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&tr->color.r, &tr->color.r, &tr->color.r);
	ft_lstadd_back(&rt->list_obj, ft_lstnew(tr));
}

void 			nul_setup(t_mini_rt *rt)
{
	rt->list_cam = NULL;
	rt->list_light = NULL;
	rt->list_obj = NULL;
}

void valid_d(double *d,t_mini_rt *rt)
{
		if(*d < 0)
			error("Invalid diametr",rt);
}
void 			ft_parse_line(char *line, t_mini_rt *rt)
{
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
	else
		return ;
}
void            ft_parser_rt(char *line,t_mini_rt *rt)
{
	rt->i = 0;
	ft_parse_line(line,rt);
}
void        	ft_make_file(t_list **list, int size,t_mini_rt *rt)
{
	char **file;
	int j;
	int m;
	t_list *tmp;
	tmp = *list;
	j = -1;
	file = calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		file[++j] = tmp->content;
		tmp = tmp->next;
	}
	j = -1;
	m = -1;
	while (file[++m])
		ft_parser_rt(file[++j],rt);
}
int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
int check_split(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

void check_vec(double *x,double *y,double *z,t_mini_rt *rt)
{
	if(*x > 1 || *x < -1 || *y > 1 || *y < -1 || *z > 1 || *z < -1)
	{
		error("Invalid vector",rt);
		return ;
	}
}

void        ft_start_parse_rt(char *map,t_mini_rt *rt)
{
	int     fd;
	char    *line;
	t_list *list;
	list = NULL;
	fd = open(map, O_RDONLY);
	while ((get_next_line(fd, &line)) > 0)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
	}
	ft_lstadd_back(&list, ft_lstnew(line));
	ft_make_file(&list, ft_lstsize(list),rt);
}
int          ft_check_rt(char *str)
{
	int     i;
	i = 0;
	while (str[i] != '.')
		i++;
	i++;
	if (str[i] == 'r' && str[i + 1] == 't' && str[i + 2] == '\0')
		return (0);
	return (1);
}

void check_cam(t_mini_rt *rt)
{
	t_list  *tmp;
	tmp = rt->list_cam;
	if (tmp == NULL)
		error("No cam's",rt);
}
//
//void            count_list(t_mini_rt *rt)
//{
//	t_list  *tmp = rt->list_cam;
//	t_cam   *ptr;
//	while (tmp != NULL)
//	{
//		ptr = tmp->content;
////		printf("%f\n", ptr->x);
//		tmp = tmp->next;
//	}
//}
//void            po_listy(t_mini_rt *rt)
//{
//	t_list  *tmp = rt->list_sp;
//	t_sp   *ptr;
//
//	while (tmp != NULL)
//	{
//		ptr = tmp->content;
//		tmp = tmp->next;
//	}
//}
void valid(t_mini_rt *rt)
{
	if(rt->res.flag != 1)
		error("Invalid res",rt);
	if(rt->amb.flag != 1)
		error("Invalid amb",rt);
}
int         main(int argc, char **argv)
{
	t_mini_rt   *rt;

	if (!(rt = malloc(sizeof(t_mini_rt))))
		error("malloc is dead,you a kill him",rt);
	if (argc == 1 || argc > 3 || (argc == 3 && ft_strcmp(argv[3],"--save") != 0))
		error("Invalid number of arguments",rt);
	if(ft_check_rt(argv[1]) == 1)
		error("Invalid expansion",rt);
	if (argc == 3)
		rt->flag = 1;
	nul_setup(rt);
//	ft_start_parse_rt("../map.rt",rt);
	ft_start_parse_rt(argv[1],rt);
	check_cam(rt);
	valid(rt);
	put_images(rt);
	free_all(rt);
	return (0);
}