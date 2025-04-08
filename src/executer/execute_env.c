/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:12:35 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/08 22:13:34 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void exec_env(t_minishell *mshell)
{
	t_env_node	*node;

	node = mshell->envs->env;
	while (node)
	{
	printf("%s=%s\n",node->var, node->value);
	node = node->next;
	}
}
