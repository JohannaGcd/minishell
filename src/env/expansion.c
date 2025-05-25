/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 09:09:09 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 17:09:39 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executer.h"

size_t	env_var_length(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '?' || str[len] == '$')
	{
		return (1);
	}
	while (ft_isalnum(str[len]) || str[len] == '_')
	{
		len++;
	}
	return (len);
}

bool	check_is_env(char *str, int i)
{
	if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '?' || str[i + 1] == '_'))
		return (true);
	return (false);
}

size_t	calculate_new_length(char *str, t_envs *envs)
{
	size_t	i;
	size_t	new_len;
	int		var_len;
	char	*env_value;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (check_is_env(str, i))
		{
			var_len = env_var_length(str + i + 1);
			env_value = extract_env(str + i, envs, var_len);
			if (env_value)
				new_len += strlen(env_value);
			free(env_value);
			i += 1 + var_len;
		}
		else
		{
			new_len++;
			i++;
		}
	}
	return (new_len);
}

static void	handle_env_var(char *result, size_t *j, char *str, t_envs *envs)
{
	int		var_len;
	char	*env_value;

	var_len = env_var_length(str + 1);
	env_value = extract_env(str, envs, var_len);
	if (env_value)
	{
		strcpy(result + *j, env_value);
		*j += strlen(env_value);
		free(env_value);
	}
}

void	fill_result(char *result, char *str, t_envs *envs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_is_env(str, i))
		{
			handle_env_var(result + j, &j, str + i, envs);
			i += 1 + env_var_length(str + i + 1);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*change_all_env(char *str, t_envs *envs)
{
	size_t	new_len;
	char	*result;

	new_len = calculate_new_length(str, envs);
	result = malloc(new_len + 1);
	if (!result)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	fill_result(result, str, envs);
	return (result);
}

// char	*change_all_env(char *str, t_envs *envs)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	new_len;
// 	size_t	var_len;
// 	char	*result;
// 	char	*env_value;

// 	i = 0;
// 	j = 0;
// 	new_len = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && (ft_isalnum(str[i + 1])
// 				|| str[i + 1] == '?' || str[i + 1] == '_'))
// 		{
// 			var_len = env_var_length(str + i + 1);
// 			env_value = extract_env(str + i, envs, var_len);
// 			if (env_value)
// 				new_len += strlen(env_value);
// 			i += 1 + var_len;
// 		}
// 		else
// 		{
// 			new_len++;
// 			i++;
// 		}
// 	}
// 	result = malloc(new_len + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && (ft_isalnum(str[i + 1])
// 				|| str[i + 1] == '?' || str[i + 1] == '_'))
// 		{
// 			var_len = env_var_length(str + i + 1);
// 			env_value = extract_env(str + i, envs, var_len);
// 			if (env_value)
// 			{
// 				strcpy(result + j, env_value);
// 				j += strlen(env_value);
// 			}
// 			i += 1 + var_len;
// 		}
// 		else
// 			result[j++] = str[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }