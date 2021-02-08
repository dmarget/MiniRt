//
// Created by Duncan Marget on 2/8/21.
//
#include "minirt.h"
void	free_all(t_mini_rt *rt)
{
	(void)rt;
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
void	error(char *s, t_mini_rt *rt)
{
	write(2, "Error: ", 7);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free_all(rt);
	exit(1);
}
void	check_triangle(t_vec a, t_vec b, t_vec c, t_mini_rt *rt)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		error("invalid triangle coordinates.", rt);
	if (a.x == c.x && a.y == c.y && a.z == c.z)
		error("invalid triangle coordinates.", rt);
	if (c.x == b.x && c.y == b.y && c.z == b.z)
		error("invalid triangle coordinates.", rt);
}
