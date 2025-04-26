/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_with_char.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 06:32:22 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 09:03:22 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_with_char(char *s1, char *s2, char c)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len + 2;
	dest = (char *)malloc(sizeof(char) * len);
	if (dest == NULL)
		return (NULL);
	ft_strlcat(dest, s1, len);
	ft_strlcat(dest, tmp, len);
	ft_strlcat(dest + s1_len, s2, len);
	return (dest);
}
