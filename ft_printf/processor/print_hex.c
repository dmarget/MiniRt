/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:45:16 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:45:19 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_num(t_enti *enti, int base)
{
	unsigned long res;

	res = enti->six;
	if (res < 0)
		enti->sign = 1;
	if (res == 0 && enti->precision < 0 && enti->ste != 1)
		enti->count++;
	while (res)
	{
		res = res / base;
		enti->count++;
	}
	return (enti->count);
}

static void		no_flag(t_enti *enti)
{
	int i;

	i = 0;
	count_num(enti, 16);
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
	i = 0;
	while (i++ < enti->precision_len)
		ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr_hex(enti->six, 16, enti, 'a');
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int i;

	i = 0;
	count_num(enti, 16);
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	while (i++ < enti->precision_len)
		ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr_hex(enti->six, 16, enti, 'a');
	enti->i++;
	i = 0;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int i;

	i = 0;
	count_num(enti, 16);
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
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
		ft_putnbr_hex(enti->six, 16, enti, 'a');
	enti->i++;
}

void			print_hex(t_enti *enti)
{
	enti->six = va_arg(enti->ap, unsigned int);
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
