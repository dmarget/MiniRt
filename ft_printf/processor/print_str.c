/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:46:22 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:46:25 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check(t_enti *enti)
{
	if (enti->precision == -1 && enti->ste == 1)
		enti->str_len = 0;
	if (enti->precision < enti->str_len && enti->precision != -1)
		enti->str_len = enti->precision;
	if (enti->precision < 0 && enti->ste == 2)
		enti->str_len = ft_strlen(enti->s);
	if (enti->width)
		enti->width_len = enti->width - enti->str_len;
}

static void		no_flag(t_enti *enti)
{
	int i;

	i = 0;
	enti->str_len = ft_strlen(enti->s);
	check(enti);
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
	ft_putstr(enti);
	enti->i++;
}

static void		is_minus(t_enti *enti)
{
	int i;

	i = 0;
	enti->str_len = ft_strlen(enti->s);
	check(enti);
	ft_putstr(enti);
	enti->i++;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

static void		is_null(t_enti *enti)
{
	int i;

	i = 0;
	enti->str_len = ft_strlen(enti->s);
	check(enti);
	while (i++ < enti->width_len)
		ft_putchr('0', enti);
	ft_putstr(enti);
	enti->i++;
}

void			print_str(t_enti *enti)
{
	enti->s = va_arg(enti->ap, char *);
	if (enti->s == NULL)
		enti->s = "(null)";
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
	else if (enti->zero)
		is_null(enti);
}
