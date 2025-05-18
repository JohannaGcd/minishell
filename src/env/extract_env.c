/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 07:57:17 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 07:58:42 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*extract_env(char *str, t_envs *envs, size_t len)
{
	t_env_node	*node;

	if (str[1] == '?')
	{
		return (ft_itoa(envs->status));
	}
	node = envs->env;
	while (node && ft_strncmp(node->var, str + 1,
			ft_max(len, ft_strlen(node->var))))
		node = node->next;
	if (node == NULL)
		return (NULL);
	return (ft_strdup(node->value));
}
