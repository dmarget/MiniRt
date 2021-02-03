/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:45:43 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:45:46 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		count_num_p(t_enti *enti, unsigned long base)
{
	unsigned long	res;

	res = enti->six;
	if (res == 0 && enti->precision < 0 && enti->ste != 1)
		enti->count++;
	while (res)
	{
		res /= base;
		enti->count++;
	}
	enti->count += 2;
}

static void		no_flag(t_enti *enti)
{
	int			i;

	i = 0;
	count_num_p(enti, 16);
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count + 2;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
	ft_putchr('0', enti);
	ft_putchr('x', enti);
	i = 0;
	if (enti->precision_len)
		while (i++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->count > 2)
		ft_putnbr_hex_p(enti->six, 16, enti);
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int			i;

	count_num_p(enti, 16);
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count + 2;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	ft_putchr('0', enti);
	ft_putchr('x', enti);
	i = 0;
	if (enti->precision_len)
		while (i++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->count > 2)
		ft_putnbr_hex_p(enti->six, 16, enti);
	enti->i++;
	i = 0;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int			i;

	count_num_p(enti, 16);
	if (enti->precision > enti->count && !(i = 0))
		enti->precision_len = enti->precision - enti->count + 2;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	if (enti->width && enti->precision >= 0)
	{
		while (i++ < enti->width_len)
			ft_putchr(' ', enti);
		ft_putchr('0', enti);
		ft_putchr('x', enti);
	}
	else
	{
		ft_putchr('0', enti);
		ft_putchr('x', enti);
		while (i++ < enti->width_len)
			ft_putchr('0', enti);
	}
	i = 0;
	while (i++ < enti->precision_len)
		ft_putchr('0', enti);
	enti->count > 2 && enti->i++ ? ft_putnbr_hex_p(enti->six, 16, enti) : 0;
}

void			print_p(t_enti *enti)
{
	enti->six = va_arg(enti->ap, unsigned long);
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
