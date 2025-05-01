/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 20:58:52 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/01 21:51:08 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	remove_env_var(t_envs *envs, const char *var_to_remove)
{
	t_env_node	*current;
	t_env_node	*prev;

	current = envs->env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_to_remove,
				ft_strlen(var_to_remove) + 1) == 0)
		{
			if (prev == NULL)
				envs->env = current->next;
			else
				prev->next = current->next;
			free(current->var);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	change_env_var(t_envs *envs, const char *var_to_change, char *value)
{
	t_env_node	*current;

	current = envs->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_to_change,
				ft_strlen(var_to_change) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}
