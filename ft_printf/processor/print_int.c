/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:45:30 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:45:34 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_num(t_enti *enti)
{
	int res;

	res = enti->type;
	if (res < 0)
		enti->sign = 1;
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
	int		m;

	m = 0;
	enti->type = va_arg(enti->ap, int);
	count_num(enti);
	valid(enti);
	while (m++ < enti->width_len)
		ft_putchr(' ', enti);
	if (enti->sign)
		ft_putchr('-', enti);
	m = 0;
	if (enti->precision_len)
		while (m++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->type < 0)
		enti->type = enti->type * -1;
	if (enti->count > 0)
		ft_putnbr(enti->type, enti);
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int		i;

	i = 0;
	enti->type = va_arg(enti->ap, int);
	count_num(enti);
	valid(enti);
	if (enti->sign)
		ft_putchr('-', enti);
	if (enti->precision_len)
		while (i++ < enti->precision_len)
			ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr(enti->type, enti);
	enti->i++;
	i = 0;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int		i;

	i = 0;
	enti->type = va_arg(enti->ap, int);
	count_num(enti);
	valid(enti);
	if (enti->width && enti->precision >= 0)
	{
		while (i++ < enti->width_len)
			ft_putchr(' ', enti);
		(enti->sign) ? ft_putchr('-', enti) : 0;
	}
	else
	{
		if (enti->sign)
			ft_putchr('-', enti);
		while (i++ < enti->width_len)
			ft_putchr('0', enti);
	}
	i = 0;
	while (i++ < enti->precision_len)
		ft_putchr('0', enti);
	if (enti->count > 0)
		ft_putnbr(enti->type, enti);
	enti->i++;
}

void			print_int(t_enti *enti)
{
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
