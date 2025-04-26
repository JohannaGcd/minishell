/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntaxer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:52 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/26 13:48:37 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
			return(current_token->next);
	}
	return (NULL);
}

// Checks if each token respects the syntax rules specific for its type.
int	check_token_syntax(t_token *prev_token, t_token *curr_token)
{
	int (*check_grammar_rules[])(t_token * prev_token, t_token * curr_token) = {
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
	if (check_grammar_rules[curr_token->type](prev_token, curr_token) != 0)
		return (1);
	return (0);
}

// Iterates over token_list, checks if the input respects syntax rules for BASH.
int	syntaxer(t_token *token_list)
{
	t_token	*curr_token;
	t_token	*prev_token;

	//printf("begin syntaxer\n");
	//printf("token_list%p\n", token_list);
	//printf("token_list%s\n", token_list->str);
	if (!token_list)
		return (1);
	curr_token = token_list;
	if (curr_token->type == M_SPACE && curr_token->next == NULL)
		return (1);
	//printf("token_list%s\n", token_list->str);
	prev_token = NULL;
	while (curr_token)
	{
		if (check_token_syntax(prev_token, curr_token) == 1)
			return (1);
		prev_token = curr_token;
		//printf("two syntaxer\n");
		curr_token = skip_space_token(curr_token);
	}
	return (0);
}

/* SYNTAX RULES:
clear

// 1. PIPE |
	A pipe is always followed by a second command:
		-> Pipe at the bginning or end of the line
		-> Two consecutive || without a command (WORD token) in between
		ex: | ls (pipe cannot start a command).

// 	2. COMMANDS
	A valid command consists of a command name followed by optional arguments
		-> Check the commands follows the proper order [command] [argument] [redirection]

// 2. Unclosed quotes or mismatched quotes ' "
		ex: echo "Hello (missing closing ").

// 3. Redirections < > << >>
	Input/Output Redirections or Heredoc.
		-> Check that there is a file name after < > >>
			No redirection symbols should appear without corresponding commands or arguments
		-> Missing delimiter after <<
		-> A redirective before or after a pipe should be valid
		ex: ls > (missing output file)


// 4. ENVIRONMENT VARIABLES ($)
		-> Ensure WORD token (variable name) after $
		-> Or $?
		Ex: echo $ (no variable name after $)

// 5. SPECIAL CHARACTERS
		-> DO not allow special characters (like ; or \)
*/