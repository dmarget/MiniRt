#include "minirt.h"

static t_vec get_vo(t_obj *sq,t_vec up, t_vec right,int flag)
{
	t_vec p;
	p = sum_vec(sq->vec, sum_vec(multi_vec(up,sq->d * flag / 2),multi_vec( right,sq->d * flag /2)));
	return (p);
}
static t_vec get_vs(t_obj *sq,t_vec up, t_vec right,int flag)
{
	t_vec p;
	p = sum_vec(sq->vec, sum_vec(multi_vec(up,sq->d * flag / 2),multi_vec( right,-sq->d * flag /2)));
	return (p);
}

static t_vec new_vec(double x,double y,double z)
{
	t_vec new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

static t_obj get_vector(t_vec ray,t_obj *sq)
{
	t_obj tr;
	t_vec normal;
	t_vec sky;
	t_vec right;
	t_vec up;

	normal = sq->nvec;
	if(0 > (dot_vec(sq->nvec,ray)))
		normal = multi_vec(sq->nvec,-1);
	sky = (fabs(normal.z) != 1) ? new_vec(0,0,1) : new_vec(0,1,0);
	right = vec_normalize(vec_cross(normal, sky));
	up = vec_cross(right, normal);
	tr.vec = get_vo(sq,up,right,1);
	tr.svec = get_vs(sq,up,right,-1);
	tr.xvec = get_vs(sq,up,right,1);
	tr.nvec = get_vo(sq,up,right,-1);
	return (tr);
}
double square_equal(t_obj *square,t_vec ori,t_vec dir)
{
	t_equeal eq;
	t_obj	tr;
	t_vec	hit_vec;
	t_vec	tr_ori;
	t_vec	tr_dir;

	eq.k1 = plane_equal(square,ori,dir);
	if(eq.k1 != INFINITY)
	{
		tr = get_vector(dir,square);
		tr_ori = sub_vec(tr.vec,tr.svec);
		tr_dir = sub_vec(tr.vec,tr.xvec);
		hit_vec = sub_vec(tr.vec,sum_vec(ori,multi_vec(dir,eq.k1)));
		eq.t1 = dot_vec(vec_normalize(tr_ori),hit_vec);
		eq.t2 = dot_vec(vec_normalize(tr_dir),hit_vec);
		if(0.0 <= eq.t1 && eq.t1 <= len_vec(tr_ori) && 0.0 <= eq.t2 && eq.t2 <= len_vec(tr_dir))
			return (eq.t1 > eq.t2 ? eq.t2 : eq.t1);
	}
	return (INFINITY);
}