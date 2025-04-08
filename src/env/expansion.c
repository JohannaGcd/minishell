#include "env.h"

// void find_env(char *str, int *begin, int *end)
// {
// 	int i;
// 	int flag_begin;

// 	i = 0;
// 	flag_begin = 0;
// 	while (str[i])
// 	{
// 		if(str[i] == '$')
// 		{
// 			*begin = i;
// 			flag_begin = 1;
// 			i++;
// 			continue;
// 		}
// 		else 
// 		if (flag_begin == 0)
// 		{
// 			i++;
// 			continue;
// 		}
// 		while (str[i] && str[i] != '\"' && str[i] != '/' && str[i] != ' ')
// 		{
// 			i++;
// 		}
// 		*end = i - 1;
// 		break;
// 	}
// }

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
	t_token *current_token;

	current_token = list_tokens;
	while (current_token)
	{
		if (current_token->type == ENV)
		{
			var = extract_env(current_token->str, envs,
					ft_strlen(current_token->str) - 1);
			free(current_token->str);
			if (var) 
				current_token->str = ft_strdup(var);
			else 
				current_token->str = ft_strdup("");
			current_token->type = WORD;
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
