#include "../../include/minishell.h"

t_command	*command_list_find_last(t_command *command_list_head)
{
	if (command_list_head == NULL)
		return (NULL);
	while (command_list_head->next != NULL)
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

// Counts the number of arguments in the input command
int	count_command_args(t_token *token_list)
{
	int	counter;

	counter = 0;
	while (token_list && token_list->type != PIPE)
	{
		if ((token_list->type != REDIRECT_IN)
			&& (token_list->type != REDIRECT_OUT)
			&& (token_list->type != M_SPACE))
			counter += 1;
		token_list = token_list->next;
	}
	return (counter);
}

void	copy_command_args(char **command_args, t_token *token_list)
{
	int	i;

	i = 0;
	while (token_list && token_list->type != PIPE)
	{
		if ((token_list->type != REDIRECT_IN)
			&& (token_list->type != REDIRECT_OUT)
			&& (token_list->type != M_SPACE))
		{
			command_args[i] = ft_substr(token_list->str, 0,
					ft_strlen(token_list->str));
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
	(*new_command)->command_args = malloc(sizeof(char **) * (nbr_args + 1));
	if (!(*new_command)->command_args)
	{
		perror("Failed to allocate memory for new_command->command_args");
	}
	copy_command_args((*new_command)->command_args, token_list);
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
	return (new_command);
}

// Creates a new command,
// fills it with information and appends it to the list of commands
t_command	*extract_commands(t_token *token_list)
{
	t_command	*list_command_head;
	t_command	*new_command;
	t_token		*curr_token;
	int			i;

	list_command_head = NULL;
	curr_token = token_list;
	while (curr_token)
	{
		while (curr_token && curr_token->type != PIPE)
		{
			new_command = init_command();
			if (!new_command)
			{
				perror("Failed to allocate memory in init_command");
				return (NULL);
			}
			fill_command(&new_command, token_list);
		}
		command_list_add_back(&list_command_head, new_command);
		curr_token = curr_token->next;
	}
	// for testing
	i = 0;
	while (new_command->command_args[i])
	{
		printf("new_command[%d] = %s\n", i, new_command->command_args[i]);
		i++;
	}
	return (list_command_head);
}
