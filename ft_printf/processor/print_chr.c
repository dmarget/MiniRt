/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:45:02 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:45:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			no_flag(t_enti *enti)
{
	int i;

	i = 0;
	enti->type = va_arg(enti->ap, int);
	if (enti->width)
		enti->width_len = enti->width - 1;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
	ft_putchr(enti->type, enti);
	enti->i++;
}

static void			is_minus(t_enti *enti)
{
	int i;

	i = 0;
	enti->type = va_arg(enti->ap, int);
	if (enti->width)
		enti->width_len = enti->width - 1;
	ft_putchr(enti->type, enti);
	enti->i++;
	while (i++ < enti->width_len)
		ft_putchr(' ', enti);
}

void				print_chr(t_enti *enti)
{
	if (!enti->minus && !enti->zero)
		no_flag(enti);
	else if (enti->minus)
		is_minus(enti);
}
