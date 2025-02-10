/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/13 21:31:17 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/13 22:09:11 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}
