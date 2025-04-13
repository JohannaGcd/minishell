/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:41 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/13 20:54:49 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// To set the type of the token based on the first character.
int	get_token_hint(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '\'')
		return (S_QUOTE);
	if (c == '\"')
		return (D_QUOTE);
	if (c == '<')
		return (REDIRECT_IN);
	if (c == '>')
		return (REDIRECT_OUT);
	if (c == ' ')
		return (M_SPACE);
	if (c == '$')
		return (ENV);
	return (WORD);
}

// To fill the token node, with its type and the corresponding character string
void	fill_token_info(int *current_pos, char *input_str, t_token *new_token)
{
	int	start_pos;
	int	length;

	start_pos = *current_pos;
	new_token->type = get_token_hint(input_str[*current_pos]);
	void (*get_full_token[])(int *, char *, char) = {
		[TOKEN] = NULL,
		[PIPE] = pipe_token,
		[S_QUOTE] = quote_token,
		[D_QUOTE] = quote_token,
		[REDIRECT_IN] = redirect_token,
		[REDIRECT_OUT] = redirect_token,
		[WORD] = word_token,
		[M_SPACE] = space_token,
		[ENV] = env_token,
	};
	if (get_full_token[new_token->type] != NULL)
		get_full_token[new_token->type](current_pos, input_str,
			input_str[*current_pos]);
	length = (*current_pos - start_pos);
	new_token->str = ft_substr(input_str, start_pos, length);
}

// To extract the complete list of tokens from the input string
t_token	*extract_tokens(char *input_str)
{
	t_token	*token_list_head;
	t_token	*new_token;
	int		current_pos;

	token_list_head = NULL;
	current_pos = 0;
	while (input_str[current_pos] != '\0')
	{
		new_token = create_new_token();
		fill_token_info(&current_pos, input_str, new_token);
		token_list_add_back(&token_list_head, new_token);
	}
	return (token_list_head);
}
