/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 19:06:12 by jguacide      ########   odam.nl         */
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

int	equal_in_mid(char *str)
{
	int	len;
	int	i;

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

int	equal_is_last(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '=')
		return (1);
	return (0);
}

void	not_valid(char *str, t_minishell *mshell)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" \': not a valid identifier", 2);
	mshell->envs->status = 1;
}

void	handle_equal_in_mid(char *arg, char **var, char **value)
{
	*var = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	*value = ft_substr(arg, (ft_strchr(arg, '=') - arg) + 1, ft_strlen(arg));
}
