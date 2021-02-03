/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:46:35 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:46:38 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_num(t_enti *enti)
{
	unsigned int res;

	res = va_arg(enti->ap, int);
	enti->six = res;
	if (res == 0 && enti->precision < 0 && enti->ste != 1)
		enti->count++;
	while (res)
	{
		res = res / 10;
		enti->count++;
	}
	return (enti->sign);
}

static void		no_flag(t_enti *enti)
{
	int		i;

	i = 0;
	count_num(enti);
	valid(enti);
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
	i = 0;
	if (enti->precision_len)
		while (i++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->type < 0)
		enti->type = enti->type * -1;
	if (enti->count > 0)
		ft_putnbr_u(enti->six, enti);
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int		i;

	i = 0;
	count_num(enti);
	valid(enti);
	if (enti->precision_len)
		while (i++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr_u(enti->six, enti);
	enti->i++;
	i = 0;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int		i;

	i = 0;
	count_num(enti);
	valid(enti);
	if (enti->width && enti->precision != -1)
		while (i++ < enti->width_len)
			ft_putchr(' ', enti);
	else
		while (i++ < enti->width_len)
			ft_putchr('0', enti);
	i = 0;
	while (i++ < enti->precision_len)
		ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr_u(enti->six, enti);
	enti->i++;
}

void			print_u(t_enti *enti)
{
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
