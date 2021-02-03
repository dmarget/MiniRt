/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:07 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/08 13:23:27 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (++len);
}

char		*ft_itoa(int n)
{
	int		len;
	int		minus;
	char	*str;

	len = ft_numlen(n);
	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	minus = 0;
	if (n < 0)
	{
		minus = 1;
		str[0] = '-';
		n = -n;
	}
	--len;
	while (len >= (minus ? 1 : 0))
	{
		str[len] = n % 10 + '0';
		n /= 10;
		--len;
	}
	return (str);
}
