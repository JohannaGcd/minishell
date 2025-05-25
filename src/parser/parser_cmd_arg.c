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

void	copy_command_args(char **command_args, t_token *token_list)
{
	int	i;

	i = 0;
	skip_initial_tokens(&token_list);
	while (token_list && token_list->type != PIPE)
	{
		if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT)
			skip_redirection_tokens(&token_list);
		process_argument(&token_list, command_args, &i);
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
	if (nbr_args < 0)
	{
		perror("Failed to count command arguments");
		return;
	}
	commands = (char **)malloc(sizeof(char *) * (nbr_args + 1));
	if (!commands)
	{
		perror("Failed to allocate memory for new_command->command_args");
		return;
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
