/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:52:46 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/02/24 13:29:37 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int arg)
{
	if (arg <= 'Z' && arg >= 'A')
		return (arg + 32);
	else
		return (arg);
}

//return (arg + 32 * (arg <= 'Z' && arg >= 'A'));
/* int	main(void)
{
	char s;
    char result;
    
    s = '5';
	result = ft_tolower(s);
	printf("char %c ft_tolower result %c \n", s, result);
	
    s = 'a';
	result = ft_tolower(s);
	printf("char %c ft_tolower result %c \n", s, result);

	s = 'M';
	result = ft_tolower(s);
	printf("char %c ft_tolower result %c \n", s, result);

	return (0);
} */