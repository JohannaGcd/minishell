/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:11:05 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/09 10:52:24 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isdigit(int s)
{
	if (s <= '9' && s >= '0')
		return (1);
	return (0);
}

/* int	main(void)
{
	char s = '5';
	int result;
	result = ft_isdigit(s);
	printf("char %c isdigit result %d \n", s, result);
	s = 'd';
	result = ft_isdigit(s);
	printf("char %c isdigit result %d \n", s, result);
	s = 'G';
	result = ft_isdigit(s);
	printf("char %c isdigit result %d \n", s, result);
	s = '*';
	result = ft_isdigit(s);
	printf("char %c isdigit result %d \n", s, result);
	s = -1;
	result = ft_isdigit(s);
	printf("char %c isdigit result %d \n", s, result);
	return (0);
} */