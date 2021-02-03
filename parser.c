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
			ints_error();
		rt->res.x = ft_atoi(rt->split[1]);
		rt->res.y = ft_atoi(rt->split[2]);
		rt->res.x > 2560 ? rt->res.x = 2560 : 0;
		rt->res.y > 1440 ? rt->res.y = 1395 : 0;
		rt->res.flag = 1;
		if(rt->res.x < 1 || rt->res.y < 1)
			write(1,"ERROR",5);
}
//              ПАРСИМ ОСВЕЩЕНИЕ
void            ft_parse_amb(char *line, t_mini_rt *rt)
{
	if(*line == '\0')
		return ;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=3)
		ints_error();
	rt->amb.range = ft_atof(rt->split[1]);
//	printf("%f",rt->amb.range);
	if(rt->amb.range < 0 || rt->amb.range > 1)
		ints_error();
	rt->split_rgb = ft_split(rt->split[2], ',');
	rt->amb.color.r = ft_atoi(rt->split_rgb[0]);
	rt->amb.color.g = ft_atoi(rt->split_rgb[1]);
	rt->amb.color.b = ft_atoi(rt->split_rgb[2]);
	check_rgb(&rt->amb.color.r,&rt->amb.color.g,&rt->amb.color.b);
}
// 				ПАРСИМ КАМЕРЫ
void			ft_parse_cam(char *line, t_mini_rt *rt)
{
	t_cam  *tmp;
	tmp = malloc(sizeof(t_cam));
//	if (!tmp->i)
//		tmp->i = 0;
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		ints_error();
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
	check_vec(&tmp->nvec.x,&tmp->nvec.y,&tmp->nvec.z);
	tmp->FOV = ft_atoi(rt->split[3]);
	if(tmp->FOV < 1 || tmp->FOV >= 180)
		ints_error();
	tmp->flag = 1;
//	tmp->i += 1;
	ft_lstadd_back(&rt->list_cam, ft_lstnew(tmp));
}
//				Парсим свет
void      		ft_parse_light(char *line, t_mini_rt *rt)
{
	t_light   *tmp;
	tmp = malloc(sizeof(t_light));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f	")) !=4)
		ints_error();
	rt->split_xyz = ft_split(rt->split[1], ',');
	tmp->vec.x = ft_atof(rt->split_xyz[0]);
	tmp->vec.y = ft_atof(rt->split_xyz[1]);
	tmp->vec.z = ft_atof(rt->split_xyz[2]);
	tmp->range = ft_atof(rt->split[2]);
	if(tmp->range > 1 || tmp->range < -1)
		ints_error();
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
	pl = malloc(sizeof(t_obj));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		ints_error();
	pl->id = 2;
	rt->split_xyz = ft_split(rt->split[1], ',');
	pl->vec.x = ft_atof(rt->split_xyz[0]);
	pl->vec.y = ft_atof(rt->split_xyz[1]);
	pl->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	pl->nvec.x = ft_atof(rt->split_xyz[0]);
	pl->nvec.y = ft_atof(rt->split_xyz[1]);
	pl->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&pl->nvec.x,&pl->nvec.y,&pl->nvec.z);
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
	sp = malloc(sizeof(t_obj));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		ints_error();
	sp->id = 1;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sp->vec.x = ft_atof(rt->split_xyz[0]) * -1;
	sp->vec.y = ft_atof(rt->split_xyz[1]);
	sp->vec.z = ft_atof(rt->split_xyz[2]);
	sp->d = ft_atof(rt->split[2]);
	valid_d(&sp->d);
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
	sq = malloc(sizeof(t_obj));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=5)
		ints_error();
	sq->id = 3;
	rt->split_xyz = ft_split(rt->split[1], ',');
	sq->vec.x = ft_atof(rt->split_xyz[0]);
	sq->vec.y = ft_atof(rt->split_xyz[1]);
	sq->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	sq->nvec.x = ft_atof(rt->split_xyz[0]);
	sq->nvec.y = ft_atof(rt->split_xyz[1]);
	sq->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&sq->nvec.x,&sq->nvec.y,&sq->nvec.z);
	sq->d = ft_atof(rt->split[3]);
	valid_d(&sq->d);
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
	cy = malloc(sizeof(t_obj));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=6)
		ints_error();
	cy->id = 4;
	rt->split_xyz = ft_split(rt->split[1], ',');
	cy->vec.x = ft_atof(rt->split_xyz[0]);
	cy->vec.y = ft_atof(rt->split_xyz[1]);
	cy->vec.z = ft_atof(rt->split_xyz[2]);
	rt->split_xyz = ft_split(rt->split[2], ',');
	cy->nvec.x = ft_atof(rt->split_xyz[0]);
	cy->nvec.y = ft_atof(rt->split_xyz[1]);
	cy->nvec.z = ft_atof(rt->split_xyz[2]);
	check_vec(&cy->nvec.x, &cy->nvec.y, &cy->nvec.z);
	cy->d = ft_atof(rt->split[3]);
	valid_d(&cy->d);
	cy->h = ft_atof(rt->split[4]);
	valid_d(&cy->h);
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
	tr = malloc(sizeof(t_obj));
	if(check_split(rt->split = ft_ssplit(&line[rt->i], " /t/n/r/v/f")) !=4)
		ints_error();
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

void valid_d(double *d)
{
		if(*d < 0)
			ints_error();
}

void ints_error()
{
		printf("%s","error man,it's error");
		exit (0);
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
//	else if (line[rt->i] == '\0')
//		return ;
	else
		return ;
}
void            ft_parser_rt(char *line,t_mini_rt *rt)
{
//	t_mini_rt   *rt;
//
//	rt = malloc(sizeof(t_mini_rt));
//	nul_setup(rt);
	rt->i = 0;
	while (!ft_isalpha(line[rt->i]))
		rt->i++;
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

int check_split(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}


void check_rgb(double *r,double *g,double *b)
{
	if(*r > 255)
		*r = 255;
	if(*g > 255)
		*r = 255;
	if(*b > 255)
		*b = 255;
	if(*r < 0)
		*r = 0;
	if(*g < 0)
		*g = 0;
	if(*b < 0)
		*b = 0;
}

void check_vec(double *x,double *y,double *z)
{
	if(*x > 1 || *x < -1 || *y > 1 || *y < -1 || *z > 1 || *z < -1)
	{
		ints_error();
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
		printf("%s","error");
//		ints_error();
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
//		printf("%f\n", ptr->vec.x);
//		printf("%f\n", ptr->vec.y);
//		printf("%f\n", ptr->vec.z);
//		tmp = tmp->next;
//	}
//}
//printf("%d\n", ptr->color.r);
//printf("%d\n", ptr->color.g);
//printf("%d\n", ptr->color.b);
int         main(int argc, char **argv)
{
	t_mini_rt   *rt;

	rt = malloc(sizeof(t_mini_rt));

//	if (argc != 2 || ft_check_rt(argv[1]) == 1)
//		ints_error();
	nul_setup(rt);
	ft_start_parse_rt("../map.rt",rt);
//	ft_start_parse_rt(argv[1],rt);
	check_cam(rt);
	if(rt->res.flag != 1)
		ints_error();
//	po_listy(rt);
	put_images(rt);
	free(rt);
	return (0);
}