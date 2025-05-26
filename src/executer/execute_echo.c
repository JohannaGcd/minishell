/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 16:51:50 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/26 21:58:56 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	is_n_arg(char *arg)
{
	int	i;

	i = 1;
	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	exec_echo(char **command_args, t_minishell *mshell)
{
	int	i;
	int	is_n;

	(void)mshell;
	i = 1;
	is_n = is_n_arg(command_args[1]);
	while (command_args[i] && is_n_arg(command_args[i]))
		i++;
	while (i < number_arguments(command_args) - 1)
	{
		printf("%s ", command_args[i]);
		i++;
	}
	if (i == number_arguments(command_args) - 1)
		printf("%s", command_args[i]);
	if (is_n == 0)
		printf("\n");
	mshell->envs->status = 0;
}
