/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:18:53 by spanfilo      #+#    #+#                 */
/*   Updated: 2025/05/26 22:54:29 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	char_to_int(char n)
{
	return (n - '0');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	min_count;
	int	res;

	i = 0;
	res = 0;
	min_count = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			min_count++;
		i++;
	}
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + char_to_int(str[i]);
		i++;
	}
	if (min_count % 2 == 1)
		res = -1 * res;
	return (res);
}

long int ft_atoi_long(const char *str)
{
	int	i;
	int	min_count;
	long int	res;

	i = 0;
	res = 0;
	min_count = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			min_count++;
		i++;
	}
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + char_to_int(str[i]);
		i++;
	}
	if (min_count % 2 == 1)
		res = -1 * res;
	return (res);
}
/* int main (int argc, char **argv)
{
	char s1[20] = "  \t\n\v\f\r ++--7654ff";
	if (argc != 2)
	{
		printf("usage %s is: string" ,argv[0]);
		return (1);
	}
	printf("%s\n", argv[1]);
	printf("%d\n",ft_atoi(argv[1]));
	printf("%s\n", s1);
	printf("%d\n",ft_atoi(s1));
} */