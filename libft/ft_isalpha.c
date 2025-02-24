/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:11:35 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/02/24 13:38:41 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int s)
{
	if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))
		return (1);
	return (0);
}
/*int	main(void)
{
	char s = '5';
	int result;
	result = ft_isalpha(s);
	printf("char %c isalpha result %d \n", s, result);
	s = 'd';
	result = ft_isalpha(s);
	printf("char %c isalpha result %d \n", s, result);
	s = 'G';
	result = ft_isalpha(s);
	printf("char %c isalpha result %d \n", s, result);
	s = '*';
	result = ft_isalpha(s);
	printf("char %c isalpha result %d \n", s, result);
	return (0);
}*/