#include "../include/minishell.h"

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

size_t env_var_length(const char *str) {
    size_t len = 0;
    if (str[len] == '?' || str[len] == '$') {
        return 1;
    }
    while (ft_isalnum(str[len]) || str[len] == '_') {
        len++;
    }
    return len;
}


char *change_all_env(char *str, t_envs *envs)
{
	size_t i = 0;
	size_t j = 0;
    size_t new_len = 0;
    char *result = NULL;
    char *env_value = NULL;

    i = 0;
    while (str[i]) {
        if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?' || str[i + 1] == '_')) {
            size_t var_len = env_var_length(str + i + 1);
            env_value = extract_env(str + i, envs, var_len);
            if (env_value) {
                new_len += strlen(env_value);
            }
            i += 1 + var_len;
        } else {
            new_len++;
            i++;
        }
    }
    result = malloc(new_len + 1);
    if (!result) {
        return NULL;
    }

	i = 0;
    j = 0;
    while (str[i]) {
        if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?' || str[i + 1] == '_')) {
            size_t var_len = env_var_length(str + i + 1);
            env_value = extract_env(str + i, envs, var_len);
            if (env_value) {
                strcpy(result + j, env_value);
                j += strlen(env_value);
            }
            i += 1 + var_len;
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';

    return result;
}

int	expand_env(t_token *list_tokens, t_envs *envs)
{
	char *var;

	while (list_tokens)
	{
		if (list_tokens->type == ENV)
		{
			var = extract_env(list_tokens->str, envs, ft_strlen(list_tokens->str) - 1);
			if (var == NULL)
			{
				list_tokens->str = "";
			}
			else
			{
				free(list_tokens->str);
				list_tokens->str = ft_substr(var, 0, ft_strlen(var));
			}
			list_tokens->type = WORD;
		}
		if(list_tokens->type == D_QUOTE)
		{	
			if (ft_strchr(list_tokens->str, '$'))
			{
				var = change_all_env(list_tokens->str, envs);
				free(list_tokens->str);
				list_tokens->str = ft_substr(var, 0, ft_strlen(var));
			}
		}
		list_tokens = list_tokens->next;
	}
	if (var)
		free(var);
	return (0);
}
