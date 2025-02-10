/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 18:03:05 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/14 12:40:51 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (len);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	source[] = "hellodd";
// 	char	destination[50];
// 	char	*dst;
// 	dst = ft_strcpy(destination, source);
// 	printf("%s\n", dst);
// 	return(0);
// }