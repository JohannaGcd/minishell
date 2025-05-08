/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/07 23:32:30 by sveta         ########   odam.nl         */
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

int equal_in_mid(char *str)
{
	int	len;
	int i;

	i = 1;
	len = ft_strlen(str);
	while (i < len - 1)
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
int equal_is_last(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '=')
		return (1);
	return (0);
}
void	exec_export(char **command_args, t_minishell *mshell)
{
	int			count;
	char		*var;
	char		*value;
	t_env_node	*node;
	int			i;

	i = 1;
	count = number_arguments(command_args);
	if (count == 1)
	{
		exec_export_print(mshell);
	}
	else
	{
		while (i < count)
		{
			if (equal_in_mid(command_args[i]))
			{
				var = ft_substr(command_args[i], 0,
								ft_strchr(command_args[i],
									'=') - command_args[i]);
				value = ft_substr(command_args[i],
								(ft_strchr(command_args[i],
										'=') - command_args[i]) + 1,
								ft_strlen(command_args[i]));
				if (find_env_var(mshell->envs, var) == 0)
				{
					node = create_new_env_node(var, value);
					add_env_to_list(&(mshell->envs->env), node);
				}
				else 
					change_env_var(mshell->envs, var, value);
			}
			else if (equal_is_last(command_args[i]))
			{
				var = ft_substr(command_args[i], 0,
								ft_strchr(command_args[i], '=')
								- command_args[i]);
				value = ft_substr(command_args[i+1], 0,
								ft_strlen(command_args[i+1]));
				if (find_env_var(mshell->envs, var) == 0)
				{
					node = create_new_env_node(var, value);
					add_env_to_list(&(mshell->envs->env), node);
				}
				else 
					change_env_var(mshell->envs, var, value);
				i++;			
			}
			i++;
		}
	}
}


