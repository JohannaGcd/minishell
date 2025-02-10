/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/29 19:21:34 by sveta         #+#    #+#                 */
/*   Updated: 2025/01/01 18:00:32 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_int(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else
		return (10 + c - 'a');
}

int	ft_atoi_base(char *str, char *base)
{
	int	n;
	int	len;
	int	res;
	int	i;

	n = ft_strlen(base);
	len = ft_strlen(str);
	res = 0;
	i = 0;
	while (i < len)
	{
		res = res * n + char_to_int(str[i]);
		i++;
	}
	return (res);
}
