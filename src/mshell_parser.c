/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:47 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/22 15:35:34 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"

t_msh_state	mshell_lexer(t_minishell *mshell, int *exit_status)
{
	mshell->tokens = extract_tokens(mshell->input_str);
	if (mshell->tokens == NULL)
	{
		*exit_status = 1;
		return (MSH_CLEAN);
	}
	expand_env(mshell->tokens, mshell->envs);
	if (mshell->input_str)
	{
		free(mshell->input_str);
		mshell->input_str = NULL;
	}
	return (MSH_SYNTAXER);
}

t_msh_state	mshell_syntaxer(t_minishell *mshell, int *exit_status)
{
	(void)exit_status;
	if (syntaxer(mshell->tokens))
	{
		if (mshell->input_str)
			free(mshell->input_str);
		mshell->input_str = NULL;
		if (mshell->tokens)
			clean_tokens(mshell->tokens);
		return (MSH_READLINE);
	}
	else
		return (MSH_PARSER);
}

t_msh_state	mshell_parser(t_minishell *mshell, int *exit_status)
{
	mshell->commands = extract_commands(mshell->tokens);
	if (mshell->commands == NULL)
	{
		*exit_status = 1;
		return (MSH_CLEAN);
	}
	if (mshell->tokens)
	{
		clean_tokens(mshell->tokens);
		mshell->tokens = NULL;
	}
	return (MSH_EXECUTER);
}
