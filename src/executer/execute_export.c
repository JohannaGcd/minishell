/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/01 21:59:18 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_export_print(t_minishell *mshell)
{
	t_env_node	*node;

	node = mshell->envs->env;
	while (node)
	{
		printf ("declare -x %s=\"%s\"\n", node->var, node->value);
		node = node->next;
	}
}

void	exec_export(char **command_args, t_minishell *mshell)
{
	int			count;
	char		*var;
	char		*value;
	t_env_node	*node;

	count = 0;
	while (command_args[count])
		count++ ;
	if (count == 1)
		exec_export_print(mshell);
	else if (count == 2)
	{
		var = ft_substr(command_args[1], 0,
				ft_strchr(command_args[1],
					'=') - command_args[1]);
		value = ft_substr(command_args[1],
				(ft_strchr(command_args[1],
						'=') - command_args[1]) + 1,
				ft_strlen(command_args[1]));
		if (find_env_var(mshell->envs, var) == 0)
		{
			node = create_new_env_node(var, value);
			add_env_to_list(&(mshell->envs->env), node);
		}
		else 
			change_env_var(mshell->envs, var, value);
	}
	else if (count == 3)
	{
		var = ft_substr(command_args[1], 0,
				ft_strchr(command_args[1], '=')
				- command_args[1]);
		value = ft_substr(command_args[2], 0,
				ft_strlen(command_args[2]));
		if (find_env_var(mshell->envs, var) == 0)
		{
			node = create_new_env_node(var, value);
			add_env_to_list(&(mshell->envs->env), node);
		}
		else 
			change_env_var(mshell->envs, var, value);
	}
}
