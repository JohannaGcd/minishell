/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 21:19:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/27 18:11:02 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char *return_command_with_path(char *command, t_minishell *mshell)
{
    char    *paths;
    char    **list_of_paths;
    char    *command_with_path;
    //char    *temp_path;
    int     i;

    if (access(command, X_OK) == 0)
        return command;
    paths = extract_env("$PATH", mshell->envs, 5);
    if (!paths)
    {
        return NULL; 
    }
    //printf("paths=%s\n", paths);
    list_of_paths = ft_split(paths, ':');
    if (!list_of_paths)
    {
        free(paths);
        return NULL;
    }
    command_with_path = NULL;
    i = 0;
    while (list_of_paths[i])
    {
        // temp_path = ft_strjoin(list_of_paths[i], "/");
        // if (!temp_path)
        // {
        //     break;
        // }
        // command_with_path = ft_strjoin(temp_path, command);
        // free(temp_path);
        //printf("list_of_paths[%d]=%s\n", i, list_of_paths[i]);
        //printf("command_with_path=%s\n", command_with_path);
        command_with_path = ft_strjoin_with_char(list_of_paths[i], command, '/');
        //printf("command_with_path=%s\n\n", command_with_path);
        if (!command_with_path)
        {
            break;
        }
        if (access(command_with_path, X_OK) == 0)
        {
            i = 0;
            //printf("command founded\n");
            while (list_of_paths[i])
            {
                free(list_of_paths[i++]);
            }
            free(list_of_paths);
            free(paths);
            return (command_with_path);
        }
        free(command_with_path);
        command_with_path = NULL;
        i++;
    }
    i = 0;
    while (list_of_paths[i])
    {
        free(list_of_paths[i++]);
    }
    free(list_of_paths);
    free(paths);
    return (NULL);
}