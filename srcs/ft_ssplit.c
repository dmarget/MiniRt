/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:20 by dmarget           #+#    #+#             */
/*   Updated: 2021/12/01 13:13:23 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		in_s(char c, char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	c_w(char const *s, char *set)
{
	int			count;
	int			is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (in_s(*s, set))
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int p, char *set)
{
	size_t		len;

	len = 0;
	while (s[p])
	{
		if (in_s(s[p], set))
			return (len);
		len++;
		p++;
	}
	return (len);
}

char			**ssplit_rt(char const *s, char *set)
{
	char		**tab;
	int			i;
	int			j;
	int			k;

	i = -1;
	j = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char*) * (c_w(s, set) + 1))))
		return (NULL);
	while (s[++i])
	{
		if (!in_s(s[i], set))
		{
			if (k == 0)
				if (!(tab[j] = malloc(sizeof(char) * w_s(s, i, set) + 1)))
					return (NULL);
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		if ((in_s(s[i], set) && !in_s(s[i + 1], set) && k > 0) && (k = 0) == 0)
			j++;
	}
	tab[c_w(s, set)] = NULL;
	return (tab);
}
