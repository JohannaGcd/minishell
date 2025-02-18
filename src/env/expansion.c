#include "../include/minishell.h"

void find_env(char *str, int *begin, int *end)
{
	int i;
	int flag_begin;

	i = 0;
	flag_begin = 0;
	while (str[i])
	{
		if(str[i] == '$')
		{
			*begin = i;
			flag_begin = 1;
			i++;
			continue;
		}
		else 
		if (flag_begin == 0)
		{
			i++;
			continue;
		}
		while (str[i] && (str[i] != '\"' || str[i] != '/'))
		{
			i++;
		}
		*end = i;
		break;
	}
}

int	expand_env(t_token *list_tokens, t_envs *envs)
{
	char *tmp;
	int begin_env;
	int end_env;

	while (list_tokens)
	{
		if (list_tokens->type == ENV)
		{
			find_env(list_tokens->str, &begin_env, &end_env);
			//make var
			tmp = extract_env(list_tokens->str, envs);
			if (tmp == NULL)
			{
				list_tokens->str = "";
			}
			else
			{
				free(list_tokens->str);
				list_tokens->str = tmp;
			}
			list_tokens->type = WORD;
		}
		if(list_tokens->type == D_QUOTE)
		{	
			begin_env = 0;
			end_env = 0;
			find_env(list_tokens->str, &begin_env, &end_env);
		}
		list_tokens = list_tokens->next;
	}
	return (0);
}
