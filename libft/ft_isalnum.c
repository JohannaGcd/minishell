/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:21:56 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/09 10:39:38 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalnum(int s)
{
	if ((s <= '9' && s >= '0') || (s <= 'z' && s >= 'a')
		|| (s <= 'Z' && s >= 'A'))
		return (1);
	return (0);
}

/* int	main(void)
{
	char s = '5';
	int result;
	result = ft_isalnum(s);
	printf("char %c isalnum result %d \n", s, result);
	s = 'd';
	result = ft_isalnum(s);
	printf("char %c isalnum result %d \n", s, result);
	s = 'G';
	result = ft_isalnum(s);
	printf("char %c isalnum result %d \n", s, result);
	s = '*';
	result = ft_isalnum(s);
	printf("char %c isalnum result %d \n", s, result);
	return (0);
} */