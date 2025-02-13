/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 10:56:33 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/02/13 11:01:08 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*sub_str;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		return (ft_calloc(1, sizeof(char)));
	}
	if (start + len >= len_s)
		len = len_s - start;
	sub_str = (char *)malloc (sizeof(char) * (len + 1));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

/* int main(void)
{
	char s[20] = "123456789";
	char *str;
	str = ft_substr(s, 0, 9);
	printf("%s",str);
} */