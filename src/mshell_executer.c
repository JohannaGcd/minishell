/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_executer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:01 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/03 19:18:21 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state	mshell_executer(t_minishell *mshell)
{
	//printf("debug EXECUTER\n");
	execute_commands(mshell);
	if (mshell->isExit == 1)
		return (MSH_CLEAN);
	if (mshell->commands)
	{
		clean_commands(mshell->commands);
		mshell->commands = NULL;
	}
	return (MSH_READLINE);
}
