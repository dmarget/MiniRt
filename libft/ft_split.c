/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:57:20 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/08 13:13:23 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			n++;
		}
		s++;
	}
	return (n);
}

char			**ft_split(char const *s, char c)
{
	char	**mal;
	int		i;
	int		j;
	int		beg;

	if (!s)
		return (NULL);
	if (!(mal = malloc((sizeof(char *) * (count_words(s, c) + 1)))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count_words(s, c))
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
