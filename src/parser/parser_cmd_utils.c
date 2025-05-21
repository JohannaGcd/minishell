/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/18 15:06:33 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/21 17:46:20 by jguacide      ########   odam.nl         */
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

int	count_command_args(t_token *token_list)
{
	int counter;
	int redir_flag;

	if (!token_list)
		return (-1);
	if (token_list->type == PIPE)
		token_list = token_list->next;
	counter = 0;
	redir_flag = 0;
	while (token_list && token_list->type != PIPE)
	{
		while (token_list && token_list->type == M_SPACE)
			token_list = token_list->next;
		if (token_list && token_list->type == WORD && redir_flag == 1)
		{
			if (token_list->next)
				token_list = token_list->next;
			redir_flag = 0;
		}
		if (token_list && (token_list->type == WORD || token_list->type == ENV) && redir_flag == 0)
			counter += 1;
		if (token_list && (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT))
		{
			redir_flag = 1;
		}
		if (token_list)
			token_list = token_list->next;	
	}
	return (counter);
}

// Counts the number of arguments in the input command
// int	count_command_args(t_token *token_list)
// {
// 	int	counter;
// 	int loop;

// 	if (!token_list)
// 		return (-1);
// 	counter = 0;
// 	if (token_list->type == PIPE)
// 		token_list = token_list->next;
// 	loop = 0;
// 	while (token_list && token_list->type != PIPE)
// 	{
// 		// if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT)
// 		// 	break ;
// 		if (token_list->type == WORD)
// 		{
// 			if (loop == 0)
// 				counter += 1;
// 			if (loop >= 1 && token_list->str && token_list->str[0] == '-')
// 				counter += 1;
// 		}
// 		loop += 1;
// 		token_list = token_list->next;
// 	}
// 	//printf("nbr of args: %d\n", counter);
// 	return (counter);
// }

// //Copies each argument into command_args
void	skip_initial_tokens(t_token **token_list)
{
	if ((*token_list)->type == PIPE || (*token_list)->type == M_SPACE)
	{
		*token_list = (*token_list)->next;
	}
}

int	count_len(int len, t_token **token_list)
{
	int	len_new;

	if ((*token_list)->type == D_QUOTE || (*token_list)->type == S_QUOTE)
		len_new = len + ft_strlen((*token_list)->str) - 2;
	else
		len_new = len + ft_strlen((*token_list)->str);
	return (len_new);
}

int	correct_token(t_token **token_list)
{
	// if (*token_list && (*token_list)->type != M_SPACE
	// 	&& (*token_list)->type != PIPE
	// 	&& (*token_list)->type != REDIRECT_IN
	// 	&& (*token_list)->type != REDIRECT_OUT)
	if (*token_list && (*token_list)->type != M_SPACE
	&& (*token_list)->type != PIPE)
		return (1);
	return (0);
}