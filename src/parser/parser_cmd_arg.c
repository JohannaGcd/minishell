/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_arg.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:44 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/16 13:25:03 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*handle_quoted_arg(t_token *token)
{
	size_t	len;

	len = ft_strlen(token->str) - 2;
	if (len < 2)
		len = 0;
	return (ft_substr(token->str, 1, len));
}

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
		if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT)
			break ;
		if (token_list->type != M_SPACE)
			counter += 1;
		token_list = token_list->next;
	}
	return (counter);
}

//Copies each argument into command_args
void copy_command_args(char **command_args, t_token *token_list)
{
	int		i;
	char	*str;
	char	*str_tmp;
	size_t	len;

	i = 0;
	str = NULL;
	len = 0;
	if (token_list->type == PIPE)
		token_list = token_list->next;
	while (token_list && token_list->type != PIPE
		   && token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
	{
		free(str);
		str = NULL;
		len = 0;
		while (token_list && token_list->type != M_SPACE
			   && token_list->type != PIPE
			   && token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
		{
			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
				len += ft_strlen(token_list->str) - 2;
			else
				len += ft_strlen(token_list->str);
			str_tmp = malloc(sizeof(char)* (len + 1));
			//if (!str) 
			// {
			// 	perror("Failed to allocate memory");
			// 	exit(EXIT_FAILURE);
			// }
			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
				str_tmp = ft_strjoin(str,  handle_quoted_arg(token_list));
			else
				str_tmp = ft_strjoin(str, token_list->str);
			free(str);
			str = ft_strdup(str_tmp);
			free(str_tmp);
			token_list = token_list->next;
		}
		if (str) 
			command_args[i] = ft_strdup(str);
		else 
			command_args[i] = NULL;
		i++;
		while (token_list && token_list->type == M_SPACE)
			token_list = token_list->next;
	}
	command_args[i] = NULL;
	free(str);
}

// void	copy_command_args(char **command_args, t_token *token_list)
// {
// 	int		i;
// 	//char	*str;

// 	i = 0;
// 	if (token_list->type == PIPE)
// 		token_list = token_list->next;
// 	while (token_list && token_list->type != PIPE
// 		&& token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
// 	{
// 		if (token_list->type != M_SPACE) 
// 		{
// 			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
// 			{
// 				command_args[i] = handle_quoted_arg(token_list);
// 			}
// 			else
// 			{
// 				command_args[i] = ft_strdup(token_list->str);
// 			}
// 			i++;
// 		}
// 		token_list = token_list->next;
// 	}
// 	command_args[i] = NULL;
// }

// Counts the number of arguments, allocates space for those
// and copies each argument over.
void	fill_command(t_command **new_command, t_token *token_list)
{
	int		nbr_args;
	char	**commands;

	nbr_args = count_command_args(token_list);
	commands = (char **)malloc(sizeof(char *) * (nbr_args + 2));
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
