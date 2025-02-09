/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 13:26:51 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/10/15 11:33:36 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_in_set(char c, char const *set)
{
	size_t	set_len;
	size_t	i;

	set_len = ft_strlen(set);
	i = -1;
	while (++i < set_len)
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (start < len && ft_char_in_set(s1[start], set))
		start++;
	end = len;
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc (sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < end - start)
		str[i] = s1[i + start];
	str[i] = '\0';
	return (str);
}

// int main (void)
// {
// 	char s1[] = "aaaaaaaaa";
// 	char set[] = "a";
// 	char *res;
// 	res = ft_strtrim(s1, set);
// 	printf("res:%s",res);
// 	free(res);
// 	return(0);	
// }