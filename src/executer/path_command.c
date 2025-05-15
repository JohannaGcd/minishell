/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 21:19:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 14:51:22 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	free_split(char **split_str)
{
	int	i;

	i = 0;
	while (split_str && split_str[i])
		free(split_str[i++]);
	free(split_str);
}

char	*return_cmd_with_path(char *command, t_minishell *mshell)
{
	char	*paths;
	char	**list_of_paths;
	char	*command_with_path;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	paths = extract_env("$PATH", mshell->envs, 5);
	if (!paths)
		return (NULL);
	list_of_paths = ft_split(paths, ':');
	if (!list_of_paths)
		return (free(paths), NULL);
	command_with_path = NULL;
	i = 0;
	while (list_of_paths[i])
	{
		command_with_path = ft_strjoin_with_char(list_of_paths[i],
				command, '/');
		if (!command_with_path)
			break ;
		if (access(command_with_path, X_OK) == 0)
			return (free_split(list_of_paths), free(paths), command_with_path);
		free(command_with_path);
		i++;
	}
	free_split(list_of_paths);
	return (free(paths), NULL);
}
