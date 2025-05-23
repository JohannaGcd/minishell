/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 21:19:03 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/23 11:46:42 by jguacide      ########   odam.nl         */
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

char	*find_path(char **list_of_paths, char *command)
{
	int		i;
	char	*command_with_path;

	i = 0;
	command_with_path = NULL;
	while (list_of_paths[i])
	{
		command_with_path = ft_strjoin_with_char(list_of_paths[i],
				command, '/');
		if (!command_with_path)
		{
			perror("error with malloc");
			break ;
		}
		if (access(command_with_path, X_OK) == 0)
			return (command_with_path);
		free(command_with_path);
		i++;
	}
	return (NULL);
}

char	*return_cmd_w_path(char *command, t_minishell *mshell)
{
	char	*paths;
	char	**list_of_paths;
	char	*command_with_path;

	if (ft_strncmp(command, "./", 2) == 0 && access(command, X_OK) == 0)
		return (ft_strdup(command));
	paths = extract_env("$PATH", mshell->envs, 5);
	if (!paths)
		return (NULL);
	list_of_paths = ft_split(paths, ':');
	if (!list_of_paths)
		return (free(paths), NULL);
	command_with_path = find_path(list_of_paths, command);
	if (!command_with_path)
		return (NULL);
	free(paths);
	free_split(list_of_paths);
	return (command_with_path);
}
