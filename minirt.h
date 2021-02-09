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
//#include "mlx/mlx.h"
#include "mlx2/mlx.h"
#include <stdio.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

typedef struct  s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;
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
	int				flag;
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
	t_color			color;
}					t_obj;
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
	double			v_dot;
	t_color			color;
	t_vec			head;
	t_vec			tail;
	t_vec			dir;
	t_vec			pc;
	double			t_min;
	t_vec 			n;
	int				flag;
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
double				ft_atof_rt(char *str,t_mini_rt *rt);
t_vec				dot_matrix(t_vec r, t_vec u,t_vec n , t_vec d);
t_vec				multi_vec(t_vec vec,double s);
t_vec				vec_cross(t_vec one, t_vec two);
int					ft_atoi_rt(char *str);
double				dot_vec(t_vec one,t_vec two);
t_vec				sub_vec(t_vec one,t_vec two);
t_vec				sum_vec(t_vec one,t_vec two);
double				len_vec(t_vec vec);
t_vec				vec_normalize(t_vec v);
void            	ft_change_cam(t_mini_rt *rt);
void				save(t_mini_rt *all);
void				error(char *s, t_mini_rt *rt);
void				render(t_mini_rt *rt);
t_vec				vector(double x,double y,int w,int h,double z);
t_vec				cam_direction(t_mini_rt *rt,double x,double y);
int					create_trgb(t_color color);
t_color				color_dot_coe(t_color color1,t_color color2,double coe);
t_color				color_double_coe(t_color color1,t_color color2,double coe);
void				main_cam(t_mini_rt *rt);
void				put_images(t_mini_rt *rt);
int					revers_normal(t_mini_rt *rt);
void				free_all(t_mini_rt *rt);
void				check_triangle(t_vec a, t_vec b, t_vec c, t_mini_rt *rt);
t_vec				quadratic_cylinder(t_vec d, t_obj *cy, t_vec oc);
double				cylinder_equal(t_obj *cy,t_vec o, t_vec d);
void				nul_setup(t_mini_rt *rt);
void				find_normal(t_mini_rt *rt,t_obj *obj);
int					ft_check_rt(char *argv);
void				check_rgb(int *r,int *g,int *b);
void				normal(t_mini_rt *rt, t_obj *ptr_sp);
void				normal_cy(t_mini_rt *rt,t_obj *obj);
void				normal_plane(t_mini_rt *rt, t_obj *obj);
int					check_split(char **str);
void				check_vec(double *x,double *y,double *z,t_mini_rt *rt);
void				valid_d(double *d,t_mini_rt *rt);
double 				sphere_equal(t_obj *tmp,t_vec ori,t_vec dir);
double 				triangle_equal(t_obj *triangle,t_vec ori,t_vec dir);
double 				plane_equal(t_obj *plane, t_vec ori, t_vec dir);
double 				square_equal(t_obj *square,t_vec ori,t_vec dir);
#endif

