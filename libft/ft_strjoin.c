/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 12:54:25 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/12/17 14:09:53 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*str;

	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	else
		len_s2 = 0;
	str = (char *)malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		str[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		str[len_s1 + i] = s2[i];
	str[len_s1 + i] = '\0';
	return (str);
}
