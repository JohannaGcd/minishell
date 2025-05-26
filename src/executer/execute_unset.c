/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 20:35:46 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/26 22:20:55 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_unset(char **command_args, t_minishell *mshell)
{
	char		*var;
	int			i;

	if (command_args[1] == NULL)
		return ;
	i = 1;
	mshell->envs->status = 0;
	while (command_args[i])
	{
		var = command_args[i];
		if (var[0] == '\0' ||  ft_strrchr(var, '-') || ft_is_number(var))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			mshell->envs->status = 1;
		}
		else
		{
			remove_env_var(mshell->envs, var);
		}
		i++;
	}
}
