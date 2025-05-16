/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_with_char.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 06:32:22 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/16 17:58:14 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	copy_with_char(char *dest, char *s1, char *s2, char c)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	dest[i++] = c;
// 	j = 0;
// 	while (s2[j])
// 	{
// 		dest[i + j] = s2[i];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// }

// char	*ft_strjoin_with_char(char *s1, char *s2, char c)
// {
// 	char	*dest;
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	len;
// 	size_t	i;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	len = s1_len + s2_len + 2;
// 	dest = (char *)malloc(sizeof(char) * len);
// 	if (dest == NULL)
// 		return (NULL);
// 	copy_with_char(dest, s1, s2, c);
// 	return (dest);
// }

char	*ft_strjoin_with_char(char *s1, char *s2, char c)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len + 2;
	dest = (char *)malloc(sizeof(char) * len);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = c;
	i = 0;
	while (i < s2_len)
	{
		dest[s1_len + 1 + i] = s2[i];
		i++;
	}
	dest[s1_len + i + 1] = '\0';
	return (dest);
}