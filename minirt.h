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

#ifndef MINIRT_H
# define MINIRT_H
#include "mlx/mlx.h"
#include <stdio.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//#include "printf.h"
#include <math.h>
# define INT_MAX 2147483647

typedef struct  s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;
//typedef struct	s_vars
//{
//	t_data		img;
//	void		*mlx;
//	void		*win;
//	void		*rt;
//	int			bmp;
//}				t_vars;
typedef struct		s_color
{
	int 			r;
	int 			g;
	int 			b;
}					t_color;
typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;
typedef struct		s_amb
{
	double			range;
	t_color			color;
}					t_amb;
typedef struct		s_res
{
	int				x;
	int				y;
	int				flag;
}					t_res;
typedef struct		s_cam
{
	int				FOV;
	int				flag;
	t_vec			vec;
	t_vec			nvec;
}					t_cam;
typedef	struct		s_light
{
	t_vec			vec;
	double			range;
	t_color			color;
}					t_light;
typedef struct		s_equeal
{
	double			k1;
	double			k2;
	double			k3;
	t_vec			res;
	t_vec			cross;
	t_vec			sub;
	double			D;
	double			t1;
	double			t2;
}					t_equeal;
typedef struct		s_objects
{
	int				id;
	t_vec			vec;
	t_vec			nvec;
	t_vec			xvec;
	double			d;
	double			h;
	double			range;
	t_color			color;
	int				flag;
}					t_obj;
typedef struct 		s_clist
{
	void			*content;
	struct s_clist	*next;
	struct s_clist	*first;
}					t_clist;
typedef struct		s_mini_rt
{
	int             i;
	char            **split;
	char            **split_rgb;
	char			**split_xyz;
	t_res           res;
	t_amb           amb;
	int 			fov;
	double			intens;
	t_color			color;
	t_vec			head;
	t_vec			tail;
	t_vec			dir;
	t_vec			pc;
	double			t_min;
	t_vec 			n;
	t_vec 			vn;
	double 			vn_n;
	t_vec 			p;
	t_list			*tmp;
	t_obj			*main;
	t_list			*list_obj;
	t_list			*list_cam;
	void        	*mlx;
	void        	*win;
	t_list			*main_c;
	t_data			img;
	t_list			*list_light;
}					t_mini_rt;
t_vec				dot_matrix(t_vec r, t_vec u,t_vec n , t_vec d);
t_vec				multi_vec(t_vec vec,double s);
t_vec				vec_cross(t_vec one, t_vec two);
double				dot_vec(t_vec one,t_vec two);
t_vec				sub_vec(t_vec one,t_vec two);
t_vec				sum_vec(t_vec one,t_vec two);
double				len_vec(t_vec vec);
t_vec				vec_normalize(t_vec v);
void				save(t_mini_rt *all);
t_vec				vector(double x,double y,int w,int h,double z);
t_vec				cam_direction(t_mini_rt *rt,double x,double y);
int					create_trgb(t_color color);
t_color				color_dot(t_color color,double i);
t_color				color_sum(t_color color1,t_color color2);
t_color				color_dot_coe(t_color color1,t_color color2,double coe);
t_color				color_double_coe(t_color color1,t_color color2,double coe);
//int					main_cam(int key,t_mini_rt *rt,t_vars *var);
//int					main_cam(int key,t_mini_rt *rt);
void				main_cam(t_mini_rt *rt);
void				put_images(t_mini_rt *rt);
//void				put_images(t_mini_rt *rt,t_vars *vars);
void				ctv(t_mini_rt *rt, double x, double y);
void				nul_setup(t_mini_rt *rt);
int					ft_check_rt(char *argv);
void				check_rgb(double *r,double *g,double *b);
int					check_split(char **str);
void				check_vec(double *x,double *y,double *z);
void				ints_error();
void				valid_d(double *d);
//void				sphere_equal(t_mini_rt *rt, t_obj *tmp,t_vec ori,t_vec dir);
double 				sphere_equal(t_mini_rt *rt, t_obj *tmp,t_vec ori,t_vec dir);
//void				triangle_equal(t_mini_rt *rt,t_obj *triangle,t_vec ori,t_vec dir);
double 				triangle_equal(t_mini_rt *rt,t_obj *triangle,t_vec ori,t_vec dir);
double 				plane_equal(t_mini_rt *rt, t_obj *plane, t_vec ori, t_vec dir);
//void				plane_equal(t_mini_rt *rt, t_obj *plane, t_vec ori, t_vec dir);
//void				square_equal(t_mini_rt *rt,t_obj *square,t_vec ori,t_vec dir);
double 				square_equal(t_mini_rt *rt,t_obj *square,t_vec ori,t_vec dir);
#endif

