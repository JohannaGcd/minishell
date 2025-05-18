/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 07:54:34 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 17:37:07 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	find_env_var(t_envs *envs, const char *var_to_find)
{
	t_env_node	*current;

	current = envs->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_to_find,
				ft_strlen(var_to_find) + 1) == 0)
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}

char	*get_env_var(t_envs *envs, const char *var_to_find)
{
	t_env_node	*current;

	current = envs->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_to_find,
				ft_strlen(var_to_find) + 1) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
