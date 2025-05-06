/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:12:35 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/06 15:54:09 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int number_arguments(char **command_args)
{
	int	n;
	
	n = 0;
	while (command_args[n])
		n++;
	return (n);
}

void exec_env(char **command_args,t_minishell *mshell)
{
	t_env_node	*node;
	int	n_args;
	int only_equal;
	int i;
	
	only_equal = 1;
	n_args = number_arguments(command_args);
	i = 1;
	while (command_args[i])
	{
		if(!ft_strchr(command_args[i], '='))
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
			printf("%s=%s\n",node->var, node->value);
			node = node->next;
		}
		i = 1;
		while (command_args[i])
		{
			printf("%s\n",command_args[i]);
			i++;
		}
	}
	else
		printf("%s no such file or dir\n", command_args[i]);
		
}
