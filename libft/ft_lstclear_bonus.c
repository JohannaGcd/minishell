/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 09:52:06 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/17 11:01:00 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (*lst && del)
	{
		while (*lst)
		{
			node = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = node;
		}
	}
}
