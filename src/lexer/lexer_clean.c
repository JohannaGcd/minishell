/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_clean.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 14:19:17 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/05/02 14:53:51 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*str;
// 	struct s_token	*next;
// }					t_token;

void clean_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = tokens;
	next_token = current_token->next;
	while (current_token)
	{
		free(current_token->str);
		free(current_token);
		current_token = next_token;
	}
}