/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		free_all(t_mini_rt *rt)
{
	(void)rt;
	free(rt);
}

int			ft_check_rt(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '.')
		i++;
	i++;
	if (str[i] == 'r' && str[i + 1] == 't' && str[i + 2] == '\0')
		return (0);
	return (1);
}

void		check_rgb(int *r, int *g, int *b, t_mini_rt *rt)
{
	if (*r > 255)
		error("Invalid color", rt);
	if (*g > 255)
		error("Invalid color", rt);
	if (*b > 255)
		error("Invalid color", rt);
	if (*r < 0)
		error("Invalid color", rt);
	if (*g < 0)
		error("Invalid color", rt);
	if (*b < 0)
		error("Invalid color", rt);
}

void		error(char *s, t_mini_rt *rt)
{
	write(2, "Error: ", 7);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free_all(rt);
	exit(1);
}

void		check_triangle(t_vec a, t_vec b, t_vec c, t_mini_rt *rt)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		error("invalid triangle coordinates.", rt);
	if (a.x == c.x && a.y == c.y && a.z == c.z)
		error("invalid triangle coordinates.", rt);
	if (c.x == b.x && c.y == b.y && c.z == b.z)
		error("invalid triangle coordinates.", rt);
}
