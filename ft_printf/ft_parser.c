/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:41:27 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 17:27:00 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		parser_flag(t_enti *enti)
{
	while (enti->print[enti->i] == '-' || enti->print[enti->i] == '0')
	{
		if (enti->print[enti->i] == '-')
			enti->minus = 1;
		if (enti->print[enti->i] == '0')
			enti->zero = 1;
		enti->i++;
	}
}

static void		parser_width(t_enti *enti)
{
	if (enti->print[enti->i] == '*')
	{
		enti->width = va_arg(enti->ap, int);
		if (enti->width < 0)
		{
			enti->minus = 1;
			enti->width *= -1;
		}
		enti->i++;
	}
	else if (enti->print[enti->i] >= '0' && enti->print[enti->i] <= '9')
		enti->width = ft_atoi(&enti->print[enti->i], enti);
}

void			parser_precision(t_enti *enti)
{
	if (enti->print[enti->i] == '.')
	{
		enti->i++;
		enti->ste = 1;
		if (enti->print[enti->i] == '*')
		{
			enti->ste = 2;
			enti->precision = va_arg(enti->ap, int);
			enti->i++;
		}
		else if (enti->print[enti->i] >= '0' && enti->print[enti->i] <= '9')
		{
			enti->precision = 0;
			enti->precision = ft_atoi(&enti->print[enti->i], enti);
		}
	}
}

void			parser_type(t_enti *enti)
{
	if (enti->print[enti->i] == 'd' || enti->print[enti->i] == 'i')
		print_int(enti);
	else if (enti->print[enti->i] == 'c')
		print_chr(enti);
	else if (enti->print[enti->i] == 's')
		print_str(enti);
	else if (enti->print[enti->i] == 'p')
		print_p(enti);
	else if (enti->print[enti->i] == 'u')
		print_u(enti);
	else if (enti->print[enti->i] == 'x')
		print_hex(enti);
	else if (enti->print[enti->i] == 'X')
		print_cap_hex(enti);
	else if (enti->print[enti->i] == '%')
		print_per(enti);
}

void			ft_parser(t_enti *enti)
{
	while (enti->print[enti->i] != '\0')
	{
		while (enti->print[enti->i] != '%' && enti->print[enti->i])
		{
			ft_putchr(enti->print[enti->i], enti);
			enti->i++;
		}
		if (enti->print[enti->i] == '%')
		{
			enti->i++;
			ft_reinit(enti);
			parser_flag(enti);
			parser_width(enti);
			parser_precision(enti);
			parser_type(enti);
		}
	}
}
