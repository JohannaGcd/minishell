/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower_string.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/30 11:51:59 by sveta         #+#    #+#                 */
/*   Updated: 2025/01/01 17:59:49 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower_string(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		res[i] = ft_tolower(str[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
