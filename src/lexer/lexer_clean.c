/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_clean.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 14:19:17 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/05/12 12:26:05 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*str;
// 	struct s_token	*next;
// }					t_token;

void	clean_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = tokens;
	while (current_token)
	{
		next_token = current_token->next;
		if (current_token->str)
			free(current_token->str);
		free(current_token);
		current_token = next_token;
	}
}
