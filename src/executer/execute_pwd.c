/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/04 12:11:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/29 12:55:21 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_pwd(char **command_args, t_minishell *mshell)
{
	char	cwd[PATH_MAX];

	(void)command_args;
	if (mshell->pwd)
		printf("%s\n", mshell->pwd);
	else
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	mshell->envs->status = 0;
}
