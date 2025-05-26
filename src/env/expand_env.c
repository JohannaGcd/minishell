/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 17:08:49 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/24 10:44:49 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executer.h"

void	expand_env_variable(t_token *current_token, t_envs *envs)
{
	char	*var;
	char	*new_str;

	var = extract_env(current_token->str, envs, strlen(current_token->str) - 1);
	free(current_token->str);
	if (var)
	{
		new_str = ft_strdup(var);
		if (!new_str)
		{
			free(var);
			current_token->str = NULL;
			return ;
		}
		current_token->str = new_str;
		current_token->type = WORD;
		free(var);
	}
	else
	{
		current_token->str = ft_strdup("");
		current_token->type = WORD;
	}
}

void	process_double_quotes(t_token *current_token, t_envs *envs)
{
	char	*var;
	char	*new_str;

	if (ft_strchr(current_token->str, '$'))
	{
		if (ft_strncmp(current_token->str, "\"$\"", 4) == 0)
		{
			free(current_token->str);
			current_token->str = ft_strdup("$");
			current_token->type = WORD;
			return ;
		}
		var = change_all_env(current_token->str, envs);
		if (var)
		{
			free(current_token->str);
			new_str = ft_strdup(var);
			current_token->str = new_str;
			free(var);
		}
	}
}
// if (!new_str)
// {
// 	free(var);
// 	current_token->str = NULL;
// 	return ;
// }
// current_token->str = new_str;
// free(var);

int	expand_env(t_token *list_tokens, t_envs *envs)
{
	t_token	*current_token;

	current_token = list_tokens;
	while (current_token)
	{
		if (current_token->type == ENV)
		{
			process_dollar_sign(current_token, envs);
		}
		else if (current_token->type == D_QUOTE)
		{
			process_double_quotes(current_token, envs);
		}
		else if (current_token->type == S_QUOTE)
		{
			if (ft_strncmp(current_token->str, "'$'", 4) == 0)
			{
				free(current_token->str);
				current_token->str = ft_strdup("$");
				current_token->type = WORD;
			}
		}
		current_token = current_token->next;
	}
	return (0);
}

// int	expand_env(t_token *list_tokens, t_envs *envs)
// {
// 	char	*var;
// 	t_token	*current_token;
// 	t_token	*next_token;
// 	t_token	*last_inserted;
// 	char	**parts_env;
// 	t_token	*new_token;
// 	int		i;

// 	current_token = list_tokens;
// 	while (current_token)
// 	{
// 		if (current_token->type == ENV)
// 		{
// 			if (!(ft_strncmp(current_token->str, "$", 2) == 0
// 					&& (current_token->next == NULL
// 						|| current_token->next->type == M_SPACE)))
// 			{
// 				var = extract_env(current_token->str, envs,
// 						ft_strlen(current_token->str) - 1);
// 				free(current_token->str);
// 				if (var)
// 				{
// 					if (ft_strchr(var, ' '))
// 					{
// 						parts_env = ft_split(var, ' ');
// 						i = 0;
// 						next_token = current_token->next;
// 						current_token->str = ft_strdup(parts_env[i]);
// 						current_token->type = WORD;
// 						i++;
// 						last_inserted = current_token;
// 						while (parts_env[i])
// 						{
// 							new_token = create_token(WORD, parts_env[i]);
// 							if (!new_token)
// 							{
// 								perror("Token creation failed");
// 								exit(EXIT_FAILURE);
// 							}
// 							last_inserted->next = new_token;
// 							last_inserted = new_token;
// 							i++;
// 						}
// 						last_inserted->next = next_token;
// 						free_array(parts_env);
// 					}
// 					else
// 					{
// 						current_token->str = ft_strdup(var);
// 						current_token->type = WORD;
// 					}
// 				}
// 				else
// 				{
// 					current_token->str = ft_strdup("");
// 					current_token->type = WORD;
// 				}
// 				free(var);
// 			}
// 		}
// 		else if (current_token->type == D_QUOTE)
// 		{
// 			if (ft_strchr(current_token->str, '$'))
// 			{
// 				var = change_all_env(current_token->str, envs);
// 				if (var)
// 				{
// 					free(current_token->str);
// 					current_token->str = ft_strdup(var);
// 					free(var);
// 				}
// 			}
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (0);
// }