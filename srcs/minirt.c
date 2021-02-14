/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:51:03 by dmarget           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:06 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

static void		ft_lstclear_rt(t_list **lst, void (*del)(void*))
{
	t_list		*elem;

	if (!(lst && *lst && del))
		return ;
	while (lst && *lst)
	{
		elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = elem;
	}
}

void			ft_make_file(t_list **list, int size, t_mini_rt *rt)
{
	char		**file;
	int			j;
	int			m;
	t_list		*tmp;

	tmp = *list;
	j = -1;
	if (!(file = calloc(size + 1, sizeof(char *))))
		error("Invalid read", rt);
	while (tmp)
	{
		file[++j] = tmp->content;
		tmp = tmp->next;
	}
	j = -1;
	m = -1;
	while (file[++m])
		ft_parser_rt(file[++j], rt);
	ft_lstclear_rt(list, &free);
	free(file);
}

void			ft_start_parse_rt(char *map, t_mini_rt *rt)
{
	int			fd;
	char		*line;
	t_list		*list;
	int			al;

	list = NULL;
	fd = open(map, O_RDONLY);
	while ((al = get_next_line(fd, &line)) > 0)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
		line = NULL;
	}
	if (al == -1)
		error("gnl is dead", rt);
	ft_lstadd_back(&list, ft_lstnew(line));
	ft_make_file(&list, ft_lstsize(list), rt);
}

void			valid(t_mini_rt *rt)
{
	if (rt->res.flag != 1)
		error("Invalid res", rt);
	if (rt->amb.flag != 1)
		error("Invalid amb", rt);
}

int				main(int argc, char **argv)
{
	t_mini_rt	*rt;

	if (!(rt = malloc(sizeof(t_mini_rt))))
		error("malloc is dead,you are kill him", rt);
	if (argc == 1 || argc > 3 ||
			((argc == 3 && ft_strcmp(argv[2], "--save") != 1)))
		error("Invalid number of arguments", rt);
	if (ft_check_rt(argv[1]) == 1)
		error("Invalid expansion", rt);
	if (argc == 3)
		rt->flag = 1;
	nul_setup(rt);
	ft_start_parse_rt(argv[1], rt);
	check_cam(rt);
	valid(rt);
	images_main(rt);
	free_all(rt);
	exit(0);
}
