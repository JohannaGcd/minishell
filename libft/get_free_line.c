/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_free_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/17 09:36:35 by sveta         #+#    #+#                 */
/*   Updated: 2024/12/17 13:29:54 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*free_mem(char **line)
{
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}
