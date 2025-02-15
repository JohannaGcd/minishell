#include "../include/minishell.h"

int	expand_env(t_token *list_tokens, t_envs *envs)
{
	char *tmp;

	while (list_tokens)
	{
		if (list_tokens->type == ENV)
		{
			{
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
			}
			list_tokens->type = WORD;
		}
		list_tokens = list_tokens->next;
	}
	return (0);
}
