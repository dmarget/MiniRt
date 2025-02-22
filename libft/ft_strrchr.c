/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:11:34 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/02 17:12:02 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*st;

	st = 0;
	while (*s)
	{
		if (*s == c)
			st = (char *)s;
		s++;
	}
	if (c == 0 && *s == 0)
		return ((char *)s);
	return (st);
}
