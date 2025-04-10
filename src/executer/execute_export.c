/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/09 21:57:57 by sveta         ########   odam.nl         */
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

void	exec_export(t_command *command, t_minishell *mshell)
{
	int			count;
	char		*var;
	char		*value;
	t_env_node	*node;

	count = 0;
	while (command->command_args[count])
		count++ ;
	if (count == 1)
		exec_export_print(mshell);
	else if (count == 2)
	{
		var = ft_substr(command->command_args[1], 0,
				ft_strchr(command->command_args[1],
					'=') - command->command_args[1]);
		value = ft_substr(command->command_args[1],
				(ft_strchr(command->command_args[1],
						'=') - command->command_args[1]) + 1,
				ft_strlen(command->command_args[1]));
		node = create_new_env_node(var, value);
		add_env_to_list(&(mshell->envs->env), node);
	}
	else if (count == 3)
	{
		var = ft_substr(command->command_args[1], 0,
				ft_strchr(command->command_args[1], '=')
				- command->command_args[1]);
		value = ft_substr(command->command_args[2], 0,
				ft_strlen(command->command_args[2]));
		node = create_new_env_node(var, value);
		add_env_to_list(&(mshell->envs->env), node);
	}
}
