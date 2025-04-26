/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envs_to_envp.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 22:35:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 06:57:38 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

size_t	envs_count(t_envs *envs)
{
	int	i;
	t_env_node	*env;

	i = 0;
	env = envs->env;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char **envs_to_envp(t_envs *envs)
{
	t_env_node	*env;
	char		**envp;
	char		*envp_node;
	int			size;
	int			i;

	if (!envs)
		return (NULL);
	size = envs_count(envs);
	envp = ft_calloc(sizeof(char *), size + 1);
	env = envs->env;
	i = 0;
	while (env)
	{
		envp_node = ft_strjoin_with_char(env->var, env->value, '=');
		if (!envp_node)
			return (clean_env(&envs), NULL);
		envp[i++] = envp_node;
		env = env->next;
	}
	return (envp);
}