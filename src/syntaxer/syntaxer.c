/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntaxer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/18 10:37:38 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Placeholder function (for tokens which syntax' you can not check)
int	na_syntaxer(t_token *prev_token, t_token *curr_token)
{
	(void)prev_token;
	(void)curr_token;
	return (0);
}

// Skips space token
t_token	*skip_space_token(t_token *current_token)
{
	if (!current_token)
		return (NULL);
	if (current_token->next)
	{
		if (current_token->next->type == M_SPACE)
			return (current_token->next->next);
		else
			return (current_token->next);
	}
	return (NULL);
}

// Checks if each token respects the syntax rules specific for its type.
int	check_token_syntax(t_token *prev_token, t_token *curr_token)
{
	const t_syntax_func	check_grammar_rules[9] = {
	[TOKEN] = NULL,
	[PIPE] = pipe_syntaxer,
	[S_QUOTE] = quote_syntaxer,
	[D_QUOTE] = quote_syntaxer,
	[REDIRECT_IN] = redir_syntaxer,
	[REDIRECT_OUT] = redir_syntaxer,
	[WORD] = word_syntaxer,
	[M_SPACE] = na_syntaxer,
	[ENV] = env_syntaxer,
	};

	if (check_grammar_rules[curr_token->type]
		&& check_grammar_rules[curr_token->type](prev_token, curr_token) != 0)
		return (1);
	return (0);
}

// Syntax Checker:
// Iterates over token_list, 
// & checks whether the tokens respect grammar rules for BASH
int	syntaxer(t_token *token_list)
{
	t_token	*curr_token;
	t_token	*prev_token;

	if (!token_list)
		return (1);
	curr_token = token_list;
	if (curr_token->type == M_SPACE && curr_token->next == NULL)
		return (1);
	prev_token = NULL;
	while (curr_token)
	{
		if (check_token_syntax(prev_token, curr_token) == 1)
		{
			perror("syntax error");
			return (2);
		}
		prev_token = curr_token;
		curr_token = skip_space_token(curr_token);
	}
	return (0);
}
