/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:09:11 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/17 14:54:38 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

char	*ft_strdup_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen(char const *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *s1, char *s2);
void	ft_strclear(char *s);
int		get_next_line(int fd, char **line);

#endif
