/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/04 13:01:00 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void exec_cd(char **command_args, t_minishell *mshell)
{
    char *path;
    char cwd[PATH_MAX];

    path = command_args[1];
    if (path == NULL)
    {
        path = get_env_var(mshell->envs, "HOME");
        if (path == NULL) {
            perror("cd: HOME not set\n");
            return;
        }
    }
    if (chdir(path) == 0) 
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            change_env_var(mshell->envs, "PWD", cwd);   
        else 
            perror("getcwd failed");
    } 
    else 
        perror("cd failed");
}