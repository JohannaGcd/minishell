/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_arg.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:44 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/18 15:25:39 by sveta         ########   odam.nl         */
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
	size_t	len;

	len = 0;
	str = NULL;
	while (correct_token(token_list))
	{
		len = count_len(len, token_list);
		str_tmp = malloc(sizeof(char) * (len + 1));
		if (!str_tmp)
			perror_allocate_with_exit();
		if ((*token_list)->type == D_QUOTE || (*token_list)->type == S_QUOTE)
			str_tmp = ft_strjoin(str, handle_quoted_arg(*token_list));
		else
			str_tmp = ft_strjoin(str, (*token_list)->str);
		free(str);
		str = ft_strdup(str_tmp);
		if (!str)
			perror_allocate_with_exit();
		free(str_tmp);
		*token_list = (*token_list)->next;
	}
	return (str);
}

void	copy_command_args(char **command_args, t_token *token_list)
{
	int		i;
	char	*str;

	i = 0;
	skip_initial_tokens(&token_list);
	while (token_list && token_list->type != PIPE
		&& token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
	{
		str = build_argument_string(&token_list);
		if (str)
			command_args[i] = ft_strdup(str);
		else
			command_args[i] = NULL;
		i++;
		while (token_list && token_list->type == M_SPACE)
			token_list = token_list->next;
	}
	command_args[i] = NULL;
}

//2 ver
// void	copy_command_args(char **command_args, t_token *token_list)
// {
// 	int		i;
// 	char	*str;
// 	char	*str_tmp;
// 	size_t	len;

// 	i = 0;
// 	str = NULL;
// 	len = 0;
// 	if (token_list->type == PIPE)
// 		token_list = token_list->next;
// 	if (token_list->type == M_SPACE)
// 		token_list = token_list->next;
// 	while (token_list && token_list->type != PIPE
// 		&& token_list->type != REDIRECT_IN && token_list->type != REDIRECT_OUT)
// 	{
// 		free(str);
// 		str = NULL;
// 		len = 0;
// 		while (token_list && token_list->type != M_SPACE
// 			&& token_list->type != PIPE
// 			&& token_list->type != REDIRECT_IN
// 			&& token_list->type != REDIRECT_OUT)
// 		{
// 			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
// 				len += ft_strlen(token_list->str) - 2;
// 			else
// 				len += ft_strlen(token_list->str);
// 			str_tmp = malloc(sizeof(char) * (len + 1));
// 			if (!str_tmp)
// 			{
// 				perror("Failed to allocate memory");
// 				exit(EXIT_FAILURE);
// 			}
// 			if ((token_list->type == D_QUOTE) || (token_list->type == S_QUOTE))
// 				str_tmp = ft_strjoin(str, handle_quoted_arg(token_list));
// 			else
// 				str_tmp = ft_strjoin(str, token_list->str);
// 			free(str);
// 			str = ft_strdup(str_tmp);
// 			if (!str)
// 			{
// 				perror("Failed to allocate memory");
// 				exit(EXIT_FAILURE);
// 			}
// 			free(str_tmp);
// 			token_list = token_list->next;
// 		}
// 		if (str)
// 			command_args[i] = ft_strdup(str);
// 		else
// 			command_args[i] = NULL;
// 		i++;
// 		while (token_list && token_list->type == M_SPACE)
// 			token_list = token_list->next;
// 	}
// 	command_args[i] = NULL;
// 	free(str);
// }
//------------ 1ver
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
