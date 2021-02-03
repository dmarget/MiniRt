#include "minirt.h"
int		create_trgb(t_color color)
{
	return(color.r << 16 | color.g << 8 | color.b);
}
t_color color_dot(t_color color,double i)
{
	t_color new;
	new.r = color.r * i;
	new.g = color.g * i;
	new.b = color.b * i;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	check_rgb(&new.r,&new.g,&new.b);
	return(new);
}
t_color color_sum(t_color color1,t_color color2)
{
	t_color new;
	new.r = color1.r + color2.r;
	new.g = color1.g + color2.g;
	new.b = color1.b + color2.b;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return(new);
}
t_color color_dot_coe(t_color color1,t_color color2,double coe)
{
	t_color new;
	new.r = color1.r + color2.r * coe;
	new.g = color1.g + color2.g * coe;
	new.b = color1.b + color2.b * coe;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
//	check_rgb(&new.r,&new.g,&new.b);
	return(new);
}
t_color color_double_coe(t_color color1,t_color color2,double coe)
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
//	check_rgb(&new.r,&new.g,&new.b);
	return(new);
}