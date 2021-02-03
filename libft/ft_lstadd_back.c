/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:35:58 by dmarget           #+#    #+#             */
/*   Updated: 2020/11/05 16:51:38 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *start;

	if (lst == NULL)
		return ;
	start = *lst;
	if (start == NULL)
		(*lst) = new;
	else
	{
		while (start->next)
			start = start->next;
		start->next = new;
	}
}
