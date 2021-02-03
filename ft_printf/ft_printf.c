/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:41:49 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 17:27:21 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(char *format, ...)
{
	t_enti		*enti;

	if (!format)
		return (-1);
	if (!(enti = (t_enti *)malloc(sizeof(t_enti))))
		return (-1);
	enti->print = format;
	ft_init(enti);
	if (format)
	{
		va_start(enti->ap, format);
		ft_parser(enti);
		va_end(enti->ap);
		free(enti);
	}
	return (enti->len);
}
