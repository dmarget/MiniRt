/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:58 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/04 17:13:01 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t nlen;

	if (*s2 == 0)
		return ((char*)s1);
	nlen = ft_strlen(s2);
	while (*s1 && len-- >= nlen)
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, nlen) == 0)
			return ((char *)s1);
		s1++;
	}
	return (0);
}
