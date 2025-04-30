/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:47 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/28 06:45:43 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"

t_msh_state	mshell_lexer(t_minishell *mshell)
{
	printf("debug LEXER\n");
	mshell->tokens = extract_tokens(mshell->input_str);
	if (mshell->tokens == NULL)
		return (MSH_CLEAN);
	expand_env(mshell->tokens, mshell->envs);
	t_token *tmp;
	tmp = mshell->tokens;
	while (tmp)
	{
		printf("token_type: %d, token_str: %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	return (MSH_SYNTAXER);
}

t_msh_state	mshell_syntaxer(t_minishell *mshell)
{
	printf("debug SYNTAXER\n");
	if (syntaxer(mshell->tokens))
	{
		if (mshell->input_str)
			free(mshell->input_str);
		if (mshell->tokens)
		{
			free(mshell->tokens);
		}
		return (MSH_READLINE);
	}
	else
		return (MSH_PARSER);
}

t_msh_state	mshell_parser(t_minishell *mshell)
{
	printf("debug PARSER\n");
	mshell->commands = extract_commands(mshell->tokens);
	if (mshell->commands == NULL)
		return (MSH_CLEAN);
	return (MSH_EXECUTER);
}
