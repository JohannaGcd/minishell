/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 10:29:51 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/13 21:24:15 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0 && s[i] != (unsigned char)c)
	{
		i--;
	}
	if (i < 0)
		return (NULL);
	return ((char *)s + i);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*result;
//     char    *res_lib;
// 	char	ch;

// 	str = "1234567890";
// 	ch = 'a';
// 	result = ft_strrchr(str, ch);
// 	printf("res ft_strrchr: %s \n", result);
//     res_lib = strrchr(str, ch);
// 	printf("res strrchr: %s\n", res_lib);
// }