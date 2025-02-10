/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:45:00 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/09 10:55:19 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int s)
{
	if (s >= ' ' && s <= '~')
		return (1);
	return (0);
}

/* int	main(void)
{
	char s = '5';
	int result;
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	s = 'd';
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	s = 'G';
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	s = '*';
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	s = '	';
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	s = -1;
	result = ft_isprint(s);
	printf("char %c isprint result %d \n", s, result);
	return (0);
} */