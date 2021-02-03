/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:06:33 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/19 01:03:26 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 16

void			ft_strclear(char *s)
{
	if (!s)
		return ;
	while (*s)
		*s++ = '\0';
}

char			*check(char *remainder, char **line)
{
	char		*p_n;

	p_n = NULL;
	if (remainder)
	{
		if ((p_n = ft_strchr(remainder, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup_gnl(remainder);
			remainder = ft_strcpy(remainder, ++p_n);
		}
		else
		{
			*line = ft_strdup_gnl(remainder);
			ft_strclear(remainder);
		}
	}
	else
	{
		*line = ft_strdup_gnl("");
	}
	return (p_n);
}

int				re(int bws, char *p_n, char *r)
{
	if (bws < 0)
		return (-1);
	if (bws == 0 && !p_n)
	{
		free(r);
		return (0);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		*buf;
	int			bws;
	char		*p_n;
	static char	*remainder;

	bws = 0;
	buf = NULL;
	if (read(fd, buf, 0) < 0 || !line || fd < 0 || BUFFER_SIZE <= 0 ||
	(!(buf = (char*)malloc(BUFFER_SIZE + 1))))
		return (-1);
	p_n = check(remainder, line);
	while (!p_n && (bws = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bws] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n++ = '\0';
			free(remainder);
			remainder = ft_strdup_gnl(p_n);
		}
		*line = ft_strjoin_gnl(*line, buf);
	}
	free(buf);
	return (re(bws, p_n, remainder));
}
