//
// Created by Duncan Marget on 2/6/21.
#include "minirt.h"
int		ft_close(void **all)
{
	t_all **new;

	new = (t_all **)all;
	mlx_clear_window((*new)->mlx, (*new)->mlx_win);
	mlx_destroy_window((*new)->mlx, (*new)->mlx_win);
	exit(1);
}
int		w_close(t_info *info)
{
	mlx_destroy_window(info->id, info->window);
	exit(0);
}
void	ft_check_w_h_win(void *mlx_ptr, int x, int y, t_rt *rt)
{
	mlx_get_screen_size(mlx_ptr, &x, &y);
	if (rt->reso.width > x || rt->reso.height > y)
	{
		rt->reso.width = x;
		rt->reso.height = y;
	}
}