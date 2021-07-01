/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_rt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:20 by dmarget           #+#    #+#             */
/*   Updated: 2021/12/01 13:13:23 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		count_words(char const *s, char c, t_mini_rt *rt)
{
	int n;
	int i;
	int f;

	i = 0;
	n = 0;
	f = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			n++;
		}
		if (*s == c)
			f++;
		if (f > 2)
			error("Invalid argument ',' ", rt);
		s++;
	}
	return (n);
}

char			**ft_split_rt(char const *s, char c, t_mini_rt *rt)
{
	char	**mal;
	int		i;
	int		j;
	int		beg;

	if (!s)
		return (NULL);
	if (!(mal = malloc((sizeof(char *) * (count_words(s, c, rt) + 1)))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count_words(s, c, rt))
	{
		while (s[i] && s[i] == c)
			i++;
		beg = i;
		while (s[i] && s[i] != c)
			i++;
		mal[j] = ft_substr(s, beg, i - beg);
		i++;
	}
	mal[j] = NULL;
	return (mal);
}
