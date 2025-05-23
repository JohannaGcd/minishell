/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 17:08:49 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/23 17:42:11 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executer.h"

void	expand_env_variable(t_token *current_token, t_envs *envs)
{
	char	*var;

	var = extract_env(current_token->str, envs, strlen(current_token->str) - 1);
	free(current_token->str);
	if (var)
	{
		current_token->str = ft_strdup(var);
		current_token->type = WORD;
	}
	else
	{
		current_token->str = ft_strdup("");
		current_token->type = WORD;
	}
	free(var);
}

void	split_and_insert_tokens(t_token *current_token, const char *var)
{
	char	**parts_env;
	int		i;
	t_token	*next_token;
	t_token	*last_inserted;
	t_token	*new_token;

	parts_env = ft_split(var, ' ');
	i = 0;
	next_token = current_token->next;
	last_inserted = current_token;
	current_token->str = ft_strdup(parts_env[i++]);
	current_token->type = WORD;
	while (parts_env[i])
	{
		new_token = create_token(M_SPACE, " ");
		if (!new_token)
			perror("Token creation failed");
		last_inserted->next = new_token;
		last_inserted = new_token;
		new_token = create_token(WORD, parts_env[i]);
		if (!new_token)
			perror("Token creation failed");
		last_inserted->next = new_token;
		last_inserted = new_token;
		i++;
	}
	last_inserted->next = next_token;
	free_array(parts_env);
}

void	process_dollar_sign(t_token *current_token, t_envs *envs)
{
	char	*var;

	if (!(ft_strncmp(current_token->str, "$", 2) == 0
			&& (current_token->next == NULL
				|| current_token->next->type == M_SPACE)))
	{
		var = extract_env(current_token->str, envs,
				strlen(current_token->str) - 1);
		if (var && ft_strchr(var, ' '))
		{
			split_and_insert_tokens(current_token, var);
		}
		else
		{
			expand_env_variable(current_token, envs);
		}
	}
}

void	process_double_quotes(t_token *current_token, t_envs *envs)
{
	char	*var;

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