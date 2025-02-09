/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 16:59:12 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/13 21:23:36 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	forward_copying(char *d, char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

void	backward_copying(char *d, char *s, size_t len)
{
	size_t	i;

	i = len;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;

	if (dst == NULL && src == NULL)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	if (d < s)
		forward_copying(d, s, len);
	else if (d > s)
		backward_copying(d, s, len);
	return (dst);
}

// int main (void)
// {
// 	char s[] = "123456789";
// 	char *src = s+4;
// 	char *dst = s;
// 	char *res;
// 	printf("src:%s\n", src);
// 	printf("dst:%s\n", dst);
// 	res = memmove(dst, src, 5);
// 	printf("res:%s", res);
// 	return(0);
// }
