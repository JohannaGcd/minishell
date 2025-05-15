/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:12:35 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 09:48:27 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_env(char **command_args, t_minishell *mshell)
{
	t_env_node	*node;
	int			only_equal;
	int			i;

	only_equal = 1;
	i = 1;
	while (command_args[i])
	{
		if (!ft_strchr(command_args[i], '='))
		{
			only_equal = 0;
			break ;
		}
		i++;
	}
	node = mshell->envs->env;
	if (only_equal == 1)
	{
		while (node)
		{
			printf("%s=%s\n", node->var, node->value);
			node = node->next;
		}
		i = 1;
		while (command_args[i])
		{
			printf("%s\n", command_args[i]);
			i++;
		}
	}
	else
		perror("no such file or dir");
}
