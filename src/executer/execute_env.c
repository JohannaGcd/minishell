/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:12:35 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/16 12:04:07 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	print_env_and_args(t_env_node *env, char **command_args)
{
	int	i;
	t_env_node *cur_env;

	cur_env = env;
	i = 0;
	while (cur_env)
	{
		printf("%s=%s\n", env->var, env->value);
		cur_env = cur_env->next;
	}
	i = 1;
	while (command_args[i])
	{
		printf("%s\n", command_args[i]);
		i++;
	}
}

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
		print_env_and_args(node, command_args);
	else
		perror("no such file or dir");
}
