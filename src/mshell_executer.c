/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_executer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:01 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/22 19:37:02 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state	mshell_executer(t_minishell *mshell, int *exit_status)
{
	execute_commands(mshell, exit_status);
	if (mshell->is_exit == 1)
		return (MSH_CLEAN);
	if (mshell->commands)
	{
		clean_commands(mshell->commands);
		mshell->commands = NULL;
	}
	return (MSH_READLINE);
}
