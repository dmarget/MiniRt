//
// Created by Duncan Marget on 1/15/21.
//
#include "minirt.h"
//int		create_trgb(t_color color)
//{
//	return(color.r << 16 | color.g << 8 | color.b);
//}
//int		create_vrgb(t_vec color)
//{
//	return((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
//}
void            ctv(t_mini_rt *rt, double x, double y)
{
	t_list *cam_list;
	cam_list = rt->list_cam;
	t_cam *ptr;
	ptr = cam_list->content;
//	rt->x = (double)x / (double)rt->res.y * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->x = (double)x / (double)rt->res.y * 2 * tan(ptr->FOV/2 * M_PI/180);
	rt->head.x = (double)x / (double)rt->res.y * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->head.x = (double)x * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->d.x = (double)x * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->y = (double)y / (double)rt->res.x * 2 * tan(ptr->FOV/2 * M_PI/180);
	rt->head.y = (double)y / (double)rt->res.y * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->head.y = (double)y * 2 * tan(ptr->FOV/2 * M_PI/180);
//	rt->d.y = (double)y * 2 * tan(ptr->FOV/2 * M_PI/180);
	rt->head.z = (double)1;
}



