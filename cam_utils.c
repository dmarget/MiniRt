#include "minirt.h"
void main_cam(t_mini_rt *rt)
{
	rt->main_c = rt->list_cam;
//	t_list *tmp_cam = rt->list_cam;
	t_cam *ptr_cam = rt->main_c->content;
	rt->tail = ptr_cam->vec;
	rt->dir = ptr_cam->nvec;
	rt->fov = ptr_cam->FOV;
	return ;
}
t_vec vector(double x,double y,int w,int h,double z)
{
	t_vec v;

	v.x = x / w;
	v.y = y / h;
	v.z = z;
	return (v);
}
t_vec cam_direction(t_mini_rt *rt,double x,double y)
{
	t_vec cam_right;
	t_vec cam_up;
	t_vec d;
	t_vec v;
	double fov;

	rt->dir = vec_normalize(rt->dir);
	fov = 2 * tan(rt->fov/2 * M_PI / 180);
	x *= fov;
	y *= fov;
	v = vector(x,y,rt->res.x,rt->res.y,1);
	cam_right = vec_cross((t_vec){0.0,1.0,0.0},rt->dir);
	cam_up = vec_cross(rt->dir,cam_right);
	d = dot_matrix(cam_right,cam_up,rt->dir,v);
	return(d);
}