/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:11:05 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/02/24 13:27:58 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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