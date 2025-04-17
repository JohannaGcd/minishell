/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:44 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/17 22:52:01 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Counts the number of arguments in the input command
int	count_command_args(t_token *token_list)
{
	int	counter;

	if (!token_list)
		return (-1);
	counter = 0;
	if (token_list->type == PIPE)
		token_list = token_list->next;
	while (token_list && token_list->type != PIPE)
	{
		if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT
			|| token_list->type == APPEND || token_list->type == HEREDOC)
			break ;
		if (token_list->type != M_SPACE)
			counter += 1;
		token_list = token_list->next;
	}
	return (counter);
}

// Allocates space for a redirection struct 
// & fills the corresponding type and file.
// TODO: Handle error: currently we exit without clearing the whole linkedlist.
// use ft_lstclear -> leverage void pointer (see test.c)
// OR CREATE Ft lst clear and ft list new for each struct.
void	fill_redirections(t_command **command, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == REDIRECT_IN)
		{
			(*command)->in = ft_calloc(1, sizeof(t_redirection));
			if (!(*command)->in)
			{
				perror("malloc fill_redirections failed");
				exit(EXIT_FAILURE);
			}
			if (ft_strncmp(tokens->str, "<<", 2) == 0)
				(*command)->in->type = HEREDOC;
			else
				(*command)->in->type = RED_IN;
			if (tokens->next->type == M_SPACE)
				tokens = tokens->next;
			{
				while (tokens->next->type == M_SPACE)
					tokens = tokens->next;
			}
			(*command)->in->file = ft_strdup(tokens->next->str);
		}
		else if (tokens->type == REDIRECT_OUT)
		{
			(*command)->out = ft_calloc(1, sizeof(t_redirection));
			if (!(*command)->out)
			{
				perror("malloc fill_redirections failed");
				exit(EXIT_FAILURE);
			}
			if (ft_strncmp(tokens->str, ">>", 2) == 0)
				(*command)->out->type = APPEND;
			else
				(*command)->out->type = RED_OUT;
			if (tokens->next->type == M_SPACE)
				tokens = tokens->next;
			{
				while (tokens->next->type == M_SPACE)
					tokens = tokens->next;
			}
			(*command)->out->file = ft_strdup(tokens->next->str);
		}
		tokens = tokens->next;
	}
}

void	copy_command_args(char **command_args, t_token *token_list)
{
	int	i;

	i = 0;
	if (token_list->type == PIPE)
		token_list = token_list->next;
	while (token_list && token_list->type != PIPE
		&& token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
	{
		if (token_list->type != M_SPACE)
		{
			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
			{
				command_args[i] = ft_substr(token_list->str, 1,
						ft_strlen(token_list->str) - 2);
			}
			else
			{
				command_args[i] = ft_substr(token_list->str, 0,
						ft_strlen(token_list->str));
			}
			if (!command_args)
			{
				perror("Failed to allocate memory in copy_command_args");
			}
			i++;
		}
		token_list = token_list->next;
	}
	command_args[i] = NULL;
}

// Counts the number of arguments, allocates space for those
// and copies each argument over.
void	fill_command(t_command **new_command, t_token *token_list)
{
	int	nbr_args;

	nbr_args = count_command_args(token_list);
	printf("cmd args nbr: %d\n", nbr_args);
	(*new_command)->command_args = malloc(sizeof(char **) * (nbr_args + 1));
	if (!(*new_command)->command_args)
	{
		perror("Failed to allocate memory for new_command->command_args");
	}
	copy_command_args((*new_command)->command_args, token_list);
	fill_redirections(new_command, token_list);
}

t_command	*extract_commands(t_token *token_list)
{
	t_command	*list_command_head;
	t_command	*new_command;
	int			i;

	list_command_head = NULL;
	while (token_list)
	{
		new_command = init_command();
		if (!new_command)
		{
			perror("Failed to allocate memory in init_command");
			return (NULL);
		}
		fill_command(&new_command, token_list);
		command_list_add_back(&list_command_head, new_command);
		token_list = skip_to_pipe(token_list);
		if (token_list)
		{
			printf("debug token_list is %s\n", token_list->str);
			token_list = token_list->next;
		}
	}
	// for testing
	i = 0;
	while (new_command->command_args[i])
	{
		printf("debug new_command[%d] = %s\n", i, new_command->command_args[i]);
		i++;
	}
	return (list_command_head);
}

// ["echo" "Hello" "$world" NULL]
// < Makefile > out.txt > out2.txt

// **args = args_from_list(list, envp)