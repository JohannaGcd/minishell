/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:47 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/23 18:01:32 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"

t_msh_state	mshell_lexer(t_minishell *mshell, int *exit_status)
{
	mshell->tokens = extract_tokens(mshell->input_str);
	// //debug
	// t_token* tmp;
	// tmp = mshell->tokens;
	// while(tmp)
	// {
	// 	printf("token->type=%d, token_str=%s\n", tmp->type, tmp->str);
	// 	tmp= tmp->next;
	// }
	// //end debug
	if (mshell->tokens == NULL)
	{
		*exit_status = 1;
		return (MSH_CLEAN);
	}
	expand_env(mshell->tokens, mshell->envs);
	// //debug
	// printf("after expend\n");
	// tmp = mshell->tokens;
	// while(tmp)
	// {
	// 	printf("token->type=%d, token_str=%s\n", tmp->type, tmp->str);
	// 	tmp= tmp->next;
	// }
	// //end debug
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
	// //debug
	// t_command *com;
	// com = mshell->commands;
	// while(com)
	// {
	// 	int i = 0;
	// 	while (com->command_args[i])
	// 	{
	// 		printf("command[%d]=%s\n",i, com->command_args[i]);
	// 		i++;
	// 	}
	// 	com = com->next;
	// }
	// //end debug
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
