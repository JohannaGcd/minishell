/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpm.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 13:43:11 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/11 15:52:38 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2 [i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/* int	main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf ("usage: %s string1 string2 num_chars\n", argv[0]);
		return (1);
	}
	char *s1 = argv[1];
	char *s2 = argv[2];
	size_t n = atoi(argv[3]);
	int res;
	int res_ft;

	res_ft = ft_strncmp(s1, s2 , n);
	res = strncmp(s1, s2, n);
	printf("res = %i\n", res);
	printf("res_ft = %i\n", res_ft);

	return (0);
} */