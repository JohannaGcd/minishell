/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 10:38:21 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/14 15:42:13 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	find_len;

	find_len = ft_strlen(to_find);
	if (find_len == 0)
		return ((char *)str);
	if (len == 0)
		return (NULL);
	while (*str && len >= find_len)
	{
		if (!ft_strncmp(str, to_find, find_len))
			return ((char *)str);
		str++;
		len--;
	}
	return (NULL);
}

/* int	main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Usage %s : <string str>  <string to find> <len> ",argv[0]);
		return(1);
	}
	char *str = argv[1];
	char *to_find = argv[2];
    size_t len = atoi(argv[3]);
	char *res;
    //char *lib_res;

	res = ft_strnstr(str, to_find, len);
	printf("ft res:%s\n", res);

     lib_res = strnstr(str, to_find, len);
	
	
	printf("lib res:%s", lib_res);
	return(0); 
}   */