/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:29:43 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/07 18:02:11 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *st;

	st = (unsigned char *)s;
	while (n--)
	{
		if (*st == (unsigned char)c)
			return ((void *)st);
		st++;
	}
	return (NULL);
}
