/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/24 10:43:16 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/24 10:43:16 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executer.h"

static t_token	*create_and_link_token(t_token **last_inserted,
		int type, const char *str)
{
	t_token	*new_token;

	new_token = create_token(type, (char *)str);
	if (!new_token)
		perror("Token creation failed");
	(*last_inserted)->next = new_token;
	*last_inserted = new_token;
	return (new_token);
}

static void	insert_word_with_space(t_token **last_inserted, const char *word)
{
	create_and_link_token(last_inserted, M_SPACE, " ");
	create_and_link_token(last_inserted, WORD, word);
}

void	split_and_insert_tokens(t_token *current_token, const char *var)
{
	char	**parts_env;
	int		i;
	t_token	*next_token;
	t_token	*last_inserted;

	parts_env = ft_split(var, ' ');
	i = 0;
	next_token = current_token->next;
	last_inserted = current_token;
	current_token->str = ft_strdup(parts_env[i++]);
	current_token->type = WORD;
	while (parts_env[i])
		insert_word_with_space(&last_inserted, parts_env[i++]);
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
		if (var)
			free(var);
	}
}
