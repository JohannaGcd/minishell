/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:30 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/23 14:41:46 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// To create and initialise an empty token with default values
t_token	*create_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token) * 1);
	if (new == NULL)
		return (NULL);
	new->type = TOKEN;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

// Creates an empty token and initialises it with default values.
t_token	*create_token(int type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token) * 1);
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

// To add a token node to the list of existing tokens
void	token_list_add_back(t_token **token_list_head, t_token *new_token)
{
	t_token	*tmp;

	if (token_list_head == NULL)
		return ;
	if (*token_list_head == NULL)
		*token_list_head = new_token;
	else
	{
		tmp = token_list_find_last(*token_list_head);
		tmp->next = new_token;
	}
}

// To find the last node of the list, and return it.
t_token	*token_list_find_last(t_token *token_list_node)
{
	if (token_list_node == NULL)
		return (NULL);
	while (token_list_node->next != NULL)
		token_list_node = token_list_node->next;
	return (token_list_node);
}
