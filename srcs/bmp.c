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

static	void		transfer(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static	void		bmp_hdr(t_mini_rt *all, int file_size, int fd)
{
	unsigned char	btr[54];

	ft_bzero(btr, 54);
	btr[0] = (unsigned char)('B');
	btr[1] = (unsigned char)('M');
	transfer(file_size, btr + 2);
	btr[10] = (unsigned char)(54);
	btr[14] = (unsigned char)(40);
	transfer(all->res.x, btr + 18);
	transfer(all->res.y, btr + 22);
	btr[26] = (unsigned char)(1);
	btr[28] = (unsigned char)(24);
	write(fd, btr, 54);
}

static	void		get_pxl(t_mini_rt *all, int fd)
{
	int				i;
	int				j;
	int				cvet;

	i = all->res.y - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < all->res.x)
		{
			cvet = *(int*)(all->img.addr + (i * all->img.line_length +
						j * (all->img.bits_per_pixel / 8)));
			write(fd, &cvet, 3);
		}
		i--;
	}
}

void				save(t_mini_rt *all)
{
	int	fd;
	int	limb;

	while (all->res.x % 4 != 0)
		all->res.x--;
	limb = 54 + (4 * all->res.y * all->res.x);
	if (!(fd = open("screen.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 0666)))
		error("bad open", all);
	bmp_hdr(all, limb, fd);
	get_pxl(all, fd);
	close(fd);
	exit(0);
}
