/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:42:58 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:43:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(t_enti *enti)
{
	int i;

	i = 0;
	while (i < enti->str_len)
	{
		ft_putchr(enti->s[i], enti);
		i++;
	}
}

void	ft_reinit(t_enti *enti)
{
	enti->count = 0;
	enti->sign = 0;
	enti->minus = 0;
	enti->zero = 0;
	enti->width = 0;
	enti->width_len = 0;
	enti->precision = -1;
	enti->precision_len = 0;
	enti->ste = 0;
	enti->type = 0;
	enti->s = "\0";
	enti->str_len = 0;
}

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_init(t_enti *enti)
{
	enti->i = 0;
	enti->count = 0;
	enti->len = 0;
	enti->sign = 0;
	enti->minus = 0;
	enti->zero = 0;
	enti->width = 0;
	enti->width_len = 0;
	enti->precision = -1;
	enti->precision_len = 0;
	enti->ste = 0;
	enti->type = 0;
	enti->s = "\0";
	enti->str_len = 0;
}
