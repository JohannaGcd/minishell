/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_msh_clean.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:49:27 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 08:51:58 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh_state	fn_msh_clean(t_minishell *mshell)
{
	printf("debug CLEAN\n");
	if (mshell->input_str)
		free(mshell->input_str);
	if (mshell->tokens)
		free(mshell->tokens);
	if (mshell->commands)
		free(mshell->commands);
	if (mshell->envs)
		free(mshell->envs);
	return (MSH_EXIT);
}
