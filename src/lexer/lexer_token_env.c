#include "../include/minishell.h"

void	env_token(int *current_pos, char *input_str, char c)
{
	if (input_str == NULL)
		return ;
	(*current_pos)++;
	while (input_str[*current_pos] && input_str[*current_pos] != ' ')
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
	// 		while (input_str[*current_pos] && ft_isdigit(input_str[*current_pos]))
	// 			(*current_pos)++;
	// 	}
	// while (input_str[*current_pos] && (ft_isalpha(input_str[*current_pos])
	// 		|| input_str[*current_pos] == '_'))
	// 	(*current_pos)++;
}