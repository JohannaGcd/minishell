/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 20:32:25 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/30 17:56:06 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_node	*create_new_env_node(char *var, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		return (NULL);
	node->value = ft_substr(value, 0, ft_strlen(value));
	node->var = ft_substr(var, 0, ft_strlen(var));
	node->next = NULL;
	return (node);
}

void	add_env_to_list(t_env_node **list, t_env_node *node)
{
	t_env_node	*tmp;

	if (*list == NULL)
	{
		*list = node;
	}
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	init_env(char **envp, t_envs *envs)
{
	int			i;
	size_t		j;
	char		*var;
	char		*value;
	t_env_node	*node;

	i = 0;
	envs->status = 0;
	envs->env = NULL;
	while (envp[i])
	{
		j = 0;
		while (j < ft_strlen(envp[i]))
		{
			if (envp[i][j] == '=')
			{
				var = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				node = create_new_env_node(var, value);
				add_env_to_list(&(envs->env), node);
				free(var);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}

char	*extract_env(char *str, t_envs *envs, size_t len)
{
	t_env_node	*node;

	if (str[1] == '?')
	{
		printf ("debug  status is %d\n", envs->status);
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
