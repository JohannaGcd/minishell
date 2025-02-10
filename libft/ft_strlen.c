/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 13:46:41 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/12/17 13:34:04 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/* int	main(void)
{
	int len;
	len = ft_strlen("string len");
	printf("%d",len);
	return (0);
} */