/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 11:38:49 by Sveta         #+#    #+#                 */
/*   Updated: 2025/05/27 18:04:10 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(long int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	n_pos;

	len = num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	n_pos = n;
	if (n < 0)
		n_pos = -n;
	while (n_pos != 0)
	{
		str[--len] = (n_pos % 10) + '0';
		n_pos = n_pos / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_long_itoa(long int n)
{
	int					len;
	char				*str;
	unsigned long int	n_pos;

	len = num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	n_pos = n;
	if (n < 0)
		n_pos = -n;
	while (n_pos != 0)
	{
		str[--len] = (n_pos % 10) + '0';
		n_pos = n_pos / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
