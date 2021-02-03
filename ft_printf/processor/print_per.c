/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_per.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:46:01 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:46:04 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		no_flag(t_enti *enti)
{
	int			i;

	i = 0;
	if (enti->width)
		while (i++ < enti->width - 1)
			ft_putchr(' ', enti);
	ft_putchr('%', enti);
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int			i;

	i = 0;
	ft_putchr('%', enti);
	enti->i++;
	if (enti->width)
		while (i++ < enti->width - 1)
			ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int			i;

	i = 0;
	if (enti->width)
		while (i++ < enti->width - 1)
			ft_putchr('0', enti);
	ft_putchr('%', enti);
	enti->i++;
}

void			print_per(t_enti *enti)
{
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
