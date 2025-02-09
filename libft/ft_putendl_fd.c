/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 19:22:59 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/15 19:27:55 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	char	nl;

	nl = '\n';
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, &nl, 1);
}
