/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_arg.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:44 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/22 14:58:45 by jguacide      ########   odam.nl         */
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

void	copy_command_args(char **command_args, t_token *token_list)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	skip_initial_tokens(&token_list);
	while (token_list && token_list->type != PIPE)
	{
		if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT)
		{
			token_list = token_list->next;
			while (token_list && token_list->type == M_SPACE)
				token_list = token_list->next;
			if (token_list)
				token_list = token_list->next;
			while (token_list && token_list->type == M_SPACE)
				token_list = token_list->next;
		}
		while (token_list && token_list->type == M_SPACE)
			token_list = token_list->next;
		if ((token_list) && (token_list->type == WORD
				|| token_list->type == S_QUOTE || token_list->type == D_QUOTE
				|| token_list->type == ENV))
		{
			str = build_argument_string(&token_list);
			command_args[i++] = str;
		}
	}
	command_args[i] = NULL;
}

// Counts the number of arguments, allocates space for those
// and copies each argument over.
void	fill_command(t_command **new_command, t_token *token_list)
{
	int		nbr_args;
	char	**commands;

	nbr_args = count_command_args(token_list);
	commands = (char **)malloc(sizeof(char *) * (nbr_args + 1));
	if (!commands)
	{
		perror("Failed to allocate memory for new_command->command_args");
	}
	copy_command_args(commands, token_list);
	(*new_command)->command_args = commands;
	fill_redirections(new_command, token_list);
}

// Processes the tokens according to grammar and builds the command structs.
t_command	*extract_commands(t_token *token_list)
{
	t_command	*list_command_head;
	t_command	*new_command;

	list_command_head = NULL;
	while (token_list)
	{
		new_command = init_command();
		if (!new_command)
		{
			perror("Failed to allocate memory in init_command");
			clean_commands(list_command_head);
			return (NULL);
		}
		fill_command(&new_command, token_list);
		command_list_add_back(&list_command_head, new_command);
		token_list = skip_to_pipe(token_list);
		if (token_list)
		{
			token_list = token_list->next;
		}
	}
	return (list_command_head);
}
