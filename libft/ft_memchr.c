/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 17:16:31 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/13 10:33:22 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	i = 0;
	cs = (unsigned char *)s;
	while (i < n && *cs != (unsigned char)c)
	{
		i++;
		cs++;
	}
	if (i == n)
		return (NULL);
	else
		return (cs);
}
