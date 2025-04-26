/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_msh_executer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:53:01 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 08:53:04 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state	fn_msh_executer(t_minishell *mshell)
{
	printf("debug EXECUTER\n");
	execute_commands(mshell);
	if (mshell->isExit == 1)
		return (MSH_CLEAN);
	return (MSH_READLINE);
}
