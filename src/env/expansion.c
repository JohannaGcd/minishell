/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 09:09:09 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/18 08:04:21 by sveta         ########   odam.nl         */
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

char	*change_all_env(char *str, t_envs *envs)
{
	size_t	i;
	size_t	j;
	size_t	new_len;
	size_t	var_len;
	char	*result;
	char	*env_value;

	i = 0;
	j = 0;
	new_len = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '_'))
		{
			var_len = env_var_length(str + i + 1);
			env_value = extract_env(str + i, envs, var_len);
			if (env_value)
				new_len += strlen(env_value);
			i += 1 + var_len;
		}
		else
		{
			new_len++;
			i++;
		}
	}
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '_'))
		{
			var_len = env_var_length(str + i + 1);
			env_value = extract_env(str + i, envs, var_len);
			if (env_value)
			{
				strcpy(result + j, env_value);
				j += strlen(env_value);
			}
			i += 1 + var_len;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	expand_env(t_token *list_tokens, t_envs *envs)
{
	char	*var;
	t_token	*current_token;
	t_token	*next_token;
	t_token	*last_inserted;
	char	**parts_env;
	t_token	*new_token;
	int		i;

	current_token = list_tokens;
	while (current_token)
	{
		if (current_token->type == ENV)
		{
			if (!(ft_strncmp(current_token->str, "$", 2) == 0
					&& (current_token->next == NULL
						|| current_token->next->type == M_SPACE)))
			{
				var = extract_env(current_token->str, envs,
						ft_strlen(current_token->str) - 1);
				free(current_token->str);
				if (var)
				{
					if (ft_strchr(var, ' '))
					{
						parts_env = ft_split(var, ' ');
						i = 0;
						next_token = current_token->next;
						current_token->str = ft_strdup(parts_env[i]);
						current_token->type = WORD;
						i++;
						last_inserted = current_token;
						while (parts_env[i])
						{
							new_token = create_token(WORD, parts_env[i]);
							if (!new_token)
							{
								perror("Token creation failed");
								exit(EXIT_FAILURE);
							}
							last_inserted->next = new_token;
							last_inserted = new_token;
							i++;
						}
						last_inserted->next = next_token;
						free_array(parts_env);
					}
					else
					{
						current_token->str = ft_strdup(var);
						current_token->type = WORD;
					}
				}
				else
				{
					current_token->str = ft_strdup("");
					current_token->type = WORD;
				}
				free(var);
			}
		}
		else if (current_token->type == D_QUOTE)
		{
			if (ft_strchr(current_token->str, '$'))
			{
				var = change_all_env(current_token->str, envs);
				if (var)
				{
					free(current_token->str);
					current_token->str = ft_strdup(var);
					free(var);
				}
			}
		}
		current_token = current_token->next;
	}
	return (0);
}

char	*get_env_var(t_envs *envs, const char *var_to_find)
{
	t_env_node	*current;

	current = envs->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var_to_find,
				ft_strlen(var_to_find) + 1) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
