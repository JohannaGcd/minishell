/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/04 12:11:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/04 12:52:47 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_pwd(char **command_args, t_minishell *mshell)
{
	char *pwd;

	if(command_args[1])
		perror("two many arguments for pwd command");
	else
	{
		pwd = get_env_var(mshell->envs, "PWD");
		if (pwd)
			printf("%s",pwd);
	}
}