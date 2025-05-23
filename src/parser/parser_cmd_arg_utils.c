/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_arg_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:44 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/23 08:56:32 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	perror_allocate_with_exit(void)
{
	perror("Failed to allocate memory");
	exit(EXIT_FAILURE);
}

char	*build_argument_string(t_token **token_list)
{
	char	*str;
	char	*str_tmp;
	char	*tmp_quotes;
	size_t	len;

	len = 0;
	str = NULL;
	while (correct_token(token_list))
	{
		len = count_len(len, token_list);
		if ((*token_list)->type == D_QUOTE || (*token_list)->type == S_QUOTE)
		{
			tmp_quotes = handle_quoted_arg(*token_list);
			str_tmp = ft_strjoin(str, tmp_quotes);
			free(tmp_quotes);
		}
		else
			str_tmp = ft_strjoin(str, (*token_list)->str);
		free(str);
		str = str_tmp;
		*token_list = (*token_list)->next;
	}
	return (str);
}

void	skip_redirection_tokens(t_token **token_list)
{
	*token_list = (*token_list)->next;
	while (*token_list && (*token_list)->type == M_SPACE)
		*token_list = (*token_list)->next;
	if (*token_list)
		*token_list = (*token_list)->next;
	while (*token_list && (*token_list)->type == M_SPACE)
		*token_list = (*token_list)->next;
}

void	process_argument(t_token **token_list, char **command_args, int *i)
{
	char	*str;

	while (*token_list && (*token_list)->type == M_SPACE)
		*token_list = (*token_list)->next;
	if ((*token_list) && ((*token_list)->type == WORD
			|| (*token_list)->type == S_QUOTE || (*token_list)->type == D_QUOTE
			|| (*token_list)->type == ENV))
	{
		str = build_argument_string(token_list);
		command_args[(*i)++] = str;
	}
}
