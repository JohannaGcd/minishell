/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/11 21:46:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/13 20:59:30 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void exec_cd(t_command *command, t_minishell *mshell) {
    char *path = command->command_args[1]; // Get the path from command arguments
    char cwd[PATH_MAX];

    if (path == NULL)
    {
        path = getenv("HOME");
        //use our env 
        if (path == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    }

    if (chdir(path) == 0) 
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            //set env in mshell->env
            setenv("PWD", cwd, 1);   
        else 
            perror("getcwd failed");
    } 
    else 
        perror("cd failed");
}