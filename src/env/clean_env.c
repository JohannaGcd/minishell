/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 06:55:53 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/02 14:10:50 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env_node(t_env_node **env)
{
	t_env_node	*current;
	t_env_node	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		if (current->var)
		{
			free(current->var);
			current->var = NULL;
		}
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	*env = NULL;
}

void	clean_env(t_envs **envs)
{
	free_env_node(&(*envs)->env);
	free(*envs);
	*envs = NULL;
}
