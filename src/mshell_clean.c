/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_clean.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:49:27 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/02 14:53:12 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "executer.h"

t_msh_state	mshell_clean(t_minishell *mshell)
{
	//printf("debug CLEAN\n");
	if (mshell->input_str)
		free(mshell->input_str);
	if (mshell->tokens)
		clean_tokens(mshell->tokens);
	if (mshell->commands)
		free(mshell->commands);
	if (mshell->envs)
		clean_env(&(mshell->envs));
	return (MSH_EXIT);
}
