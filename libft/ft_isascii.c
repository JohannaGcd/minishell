/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:33:33 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/02/24 13:27:52 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int s)
{
	if (s >= 0 && s <= 127)
		return (1);
	return (0);
}

/* int	main(void)
{
	char s = '5';
	int result;
	result = ft_isascii(s);
	printf("char %c isascii result %d \n", s, result);
	s = 'd';
	result = ft_isascii(s);
	printf("char %c isascii result %d \n", s, result);
	s = 'G';
	result = ft_isascii(s);
	printf("char %c isascii result %d \n", s, result);
	s = '*';
	result = ft_isascii(s);
	printf("char %c isascii result %d \n", s, result);
	s = -1;
	result = ft_isascii(s);
	printf("char %c isascii result %d \n", s, result);
	return (0);
} */