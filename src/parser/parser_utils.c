/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 17:45:36 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/15 17:45:40 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" 

t_token	*skip_to_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_command	*command_list_find_last(t_command *command_list_head)
{
	if (command_list_head == NULL)
		return (NULL);
	while (command_list_head && command_list_head->next != NULL)
		command_list_head = command_list_head->next;
	return (command_list_head);
}

void	command_list_add_back(t_command **command_list_head,
		t_command *new_command)
{
	t_command	*tmp;

	if (command_list_head == NULL)
		return ;
	if (*command_list_head == NULL)
		*command_list_head = new_command;
	else
	{
		tmp = command_list_find_last(*command_list_head);
		tmp->next = new_command;
	}
}

// Allocates memory for a new command
t_command	*init_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command) * 1);
	if (!new_command)
	{
		perror("Failed to allocate memory for new_command");
		return (NULL);
	}
	new_command->next = NULL;
	return (new_command);
}
