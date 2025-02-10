/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Sveta <Sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 13:09:38 by Sveta         #+#    #+#                 */
/*   Updated: 2024/10/16 20:24:00 by Sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	n;
	int	is_word;
	int	i;

	n = 0;
	i = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] != c && is_word == 0)
		{
			is_word = 1;
			n++;
		}
		else if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (n);
}

/* void	free_all(char **res, int i)
{
	while (i > 0)
		free(res[--i]);
	free(res);
} */

char	**free_all(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

// char	*copy_word(const char *start, size_t len)
// {
// 	char	*word;

// 	word = malloc(len + 1);
// 	if (!word)
// 		return (NULL);
// 	strncpy(word, start, len);
// 	word[len] = '\0';
// 	return (word);
// }

// char	**create_array(char **res, const char *s, char c)
// {
// 	size_t		len;
// 	const char	*word_start;
// 	int         i;

// 	i = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			word_start = s;
// 			len = 0;
// 			while (*s != c && *s)
// 			{
// 				len++;
// 				s++;
// 			}
// 			res[i] = copy_word(word_start, len);
// 			if (!res[i])
// 				return (free_all(res));
// 			i++;
// 		}
// 		else
// 			s++;
// 	}
// 	return (res);
// }

char	**create_array(char **res, const char *s, char c)
{
	size_t		len;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i] != c && s[i])
			{
				len++;
				i++;
			}
			res[j] = ft_substr(s, i - len, len);
			if (!res[j])
				return (free_all(res));
			j++;
		}
		else
			i++;
	}
	return (res);
}

char	**new_array(int n)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * (n + 1));
	if (res == NULL)
		return (NULL);
	res[n] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	int			words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	if (words == 0)
		return (new_array(0));
	res = new_array(words);
	if (res == NULL)
		return (NULL);
	if (create_array(res, s, c) == NULL)
		return (NULL);
	return (res);
}

// int main(void)
// {
// 	char str[]="hello!";
// 	char c =' ';
// 	char **res;
// 	int i;

// 	res = ft_split(str, c);
// 	i = 0;
// 	while (res[i]){
// 	printf("%s\n", res[i]);
// 	i++;
// 	}
// 	return(0);
// }