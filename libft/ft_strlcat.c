/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 18:02:06 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/14 12:39:31 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	size_t			space_left;
	size_t			i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		dst_len = dstsize;
	if (dst_len == dstsize)
		return (dst_len + src_len);
	space_left = dstsize - dst_len - 1;
	i = 0;
	while (i < space_left && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* #include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf ("usage %s : dest string, src string \n",argv[0] );
        return (1);
    }
    char *dest = argv[1];
    char *src = argv[2];
		int nb = atoi(argv[3]);
    ft_strncat(dest ,src, nb);
    printf ("res after ft_strncat: %s", dest);
    return(0);
} */