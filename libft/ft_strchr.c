/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 10:29:51 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/11 12:59:48 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*result;
// 	char	*res_lib;
// 	char	ch;

// 	str = "Find a char in string";
// 	ch = 'a';
// 	result = ft_strchr(str, ch);
// 	printf("%s\n", result);
// 	res_lib = strchr(str, ch);
// 	printf("%s", res_lib);
// }