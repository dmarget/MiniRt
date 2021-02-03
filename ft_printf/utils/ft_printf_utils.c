/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:43:43 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 15:43:48 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putnbr(int n, t_enti *enti)
{
	int		res;
	long	i;

	res = 0;
	i = n;
	if (i < 0)
		i = -i;
	if (i <= 9)
	{
		res = i + '0';
		write(1, &res, 1);
		enti->len++;
	}
	else
	{
		ft_putnbr(i / 10, enti);
		ft_putnbr(i % 10, enti);
	}
}

void		ft_putnbr_u(unsigned int n, t_enti *enti)
{
	int		res;
	long	i;

	res = 0;
	i = n;
	if (i < 0)
		i = -i;
	if (i <= 9)
	{
		res = i + '0';
		write(1, &res, 1);
		enti->len++;
	}
	else
	{
		ft_putnbr(i / 10, enti);
		ft_putnbr(i % 10, enti);
	}
}

void		ft_putnbr_hex_p(unsigned long n, unsigned int base, t_enti *enti)
{
	int		res;

	res = 0;
	if (n < base)
	{
		res = n + '0';
		if (n > 9)
			res = n + 87;
		write(1, &res, 1);
		enti->len++;
	}
	else
	{
		ft_putnbr_hex_p(n / base, base, enti);
		ft_putnbr_hex_p(n % base, base, enti);
	}
}

void		ft_putnbr_hex(unsigned int n, unsigned int base, \
			t_enti *enti, char c)
{
	int		res;

	res = 0;
	if (n < base)
	{
		res = n + '0';
		if (n > 9)
			res = n + c - 10;
		write(1, &res, 1);
		enti->len++;
	}
	else
	{
		ft_putnbr_hex(n / base, base, enti, c);
		ft_putnbr_hex(n % base, base, enti, c);
	}
}

void		ft_putchr(char c, t_enti *enti)
{
	write(1, &c, 1);
	enti->len++;
}
