/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 19:28:58 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/15 20:30:26 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	long_n;

	if (n < 0)
	{
		long_n = -n;
		write(fd, "-", 1);
	}
	else
		long_n = n;
	if (long_n > 9)
		ft_putnbr_fd(long_n / 10, fd);
	ft_putchar_fd(long_n % 10 + '0', fd);
}
