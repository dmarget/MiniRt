/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:44:13 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:44:16 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		valid(t_enti *enti)
{
	if (enti->precision > enti->count)
		enti->precision_len = enti->precision - enti->count;
	if (enti->width)
		enti->width_len = enti->width - enti->precision_len - enti->count;
	if (enti->sign)
		enti->width_len--;
}
