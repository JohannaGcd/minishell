/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/04 12:11:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/19 14:52:48 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	exec_pwd(char **command_args, t_minishell *mshell)
{
	(void)command_args;
	printf("%s\n", mshell->pwd);
}
