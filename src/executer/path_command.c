/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 21:19:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 09:59:51 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*return_command_with_path(char *command, t_minishell *mshell)
{
	char	*paths;
	char	**list_of_paths;
	char	*command_with_path;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	paths = extract_env("$PATH", mshell->envs, 5);
	if (!paths)
	{
		return (NULL);
	}
	list_of_paths = ft_split(paths, ':');
	if (!list_of_paths)
	{
		free(paths);
		return (NULL);
	}
	command_with_path = NULL;
	i = 0;
	while (list_of_paths[i])
	{
		command_with_path = ft_strjoin_with_char(list_of_paths[i],
				command, '/');
		if (!command_with_path)
			break ;
		if (access(command_with_path, X_OK) == 0)
		{
			i = 0;
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
