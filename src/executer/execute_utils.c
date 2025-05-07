/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 22:28:11 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/06 22:28:47 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int number_arguments(char **command_args)
{
	int	n;
	
	n = 0;
	while (command_args[n])
		n++;
	return (n);
}
