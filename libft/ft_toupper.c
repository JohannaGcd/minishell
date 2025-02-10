/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:52:40 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/09 11:55:09 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_toupper(int arg)
{
	if (arg <= 'z' && arg >= 'a')
		return (arg - 32);
	else
		return (arg);
}

/* int	main(void)
{
	char s;
    char result;
    
    s = '5';
	result = ft_toupper(s);
	printf("char %c ft_toupper result %c \n", s, result);
	
    s = 'a';
	result = ft_toupper(s);
	printf("char %c ft_toupper result %c \n", s, result);

	return (0);
} */