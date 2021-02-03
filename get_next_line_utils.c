/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:08:46 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/17 16:46:43 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strdup_gnl(char *s)
{
	int				i;
	char			*c;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	c = (char *)malloc(i + 1);
	if (c == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

size_t				ft_strlen(char const *s)
{
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char				*ft_strjoin_gnl(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*c;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	c = (char *)malloc(j + i + 1);
	if (c == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		c[i++] = s2[j++];
	}
	free(s1);
	c[i] = '\0';
	return (c);
}

char				*ft_strchr(const char *s, int c)
{
	char			*temp;

	temp = (char *)s;
	while (*temp)
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	if (*temp == 0 && c == 0)
		return (temp);
	return (NULL);
}

char				*ft_strcpy(char *s1, char *s2)
{
	int				i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
