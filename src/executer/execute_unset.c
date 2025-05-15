/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 20:35:46 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 11:11:43 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_unset(char **command_args, t_minishell *mshell)
{
	char		*var;
	int			i;

	if (command_args[1] == NULL)
	{
		return ;
	}
	i = 1;
	while (command_args[i])
	{
		var = command_args[i];
		remove_env_var(mshell->envs, var);
		i++;
	}
}
