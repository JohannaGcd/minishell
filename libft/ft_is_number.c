/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_number.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/20 15:35:00 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/20 15:52:09 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_number(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}