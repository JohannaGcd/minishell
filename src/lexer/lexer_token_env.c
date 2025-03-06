/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_token_env.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 20:24:28 by sveta         #+#    #+#                 */
/*   Updated: 2025/03/06 22:03:38 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_token(int *current_pos, char *input_str, char c)
{
	//c = 'c';
	(void)c;
	if (input_str == NULL)
		return ;
	(*current_pos)++;
	if (input_str[*current_pos] && (input_str[*current_pos] == '$'
			|| input_str[*current_pos] == '?'))
	{
		(*current_pos)++;
		return ;
	}
	while (input_str[*current_pos] && (ft_isalnum(input_str[*current_pos])
			|| input_str[*current_pos] == '_'))
	{
		(*current_pos)++;
		// if (input_str[*current_pos] && input_str[*current_pos] == '?')
		// {
		// 	(*current_pos)++;
		// 	return ;
		// }
		// else
		// 	if (input_str[*current_pos] && ft_isdigit(input_str[*current_pos]))
		// 	{
		// 		(*current_pos)++;
		// 		while (input_str[*current_pos]
		//			&& ft_isdigit(input_str[*current_pos]))
		// 			(*current_pos)++;
		// 	}
		// while (input_str[*current_pos]
		//	&& (ft_isalpha(input_str[*current_pos])
		// 		|| input_str[*current_pos] == '_'))
		// 	(*current_pos)++;
	}
}