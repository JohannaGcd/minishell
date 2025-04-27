/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_in_exec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:17:15 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 08:18:38 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	free_array(char **args)
{
	size_t	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
