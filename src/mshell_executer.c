/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_executer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:01 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/13 16:07:26 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state	mshell_executer(t_minishell *mshell, int *exit_status)
{
	printf("debug EXECUTER\n");
	(void)exit_status; // change it
	//execute_commands(mshell, exit_status);
	if (mshell->isExit == 1)
		return (MSH_CLEAN);
	if (mshell->commands)
	{
		clean_commands(mshell->commands);
		mshell->commands = NULL;
	}
	return (MSH_READLINE);
}
