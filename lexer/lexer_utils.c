#include "../include/minishell.h"

void	pipe_token(int *current_pos, char *input_str, char c)
{
	int	i;

	if (input_str == NULL)
		return ;
	i = 0;
	while (i < 2 && input_str[*current_pos] && input_str[*current_pos] == c)
	{
		(*current_pos)++;
		i++;
	}
}

void	quote_token(int *current_pos, char *input_str, char c)
{
	if (input_str == NULL)
		return ;
	(*current_pos)++; // TODO - Jo: is this skipping necessary?
	while (input_str[*current_pos] && input_str[*current_pos] != c)
		(*current_pos)++;
	if (input_str[*current_pos])
		(*current_pos)++; // TODO -Jo : idem, check purpose
}

void	redirect_token(int *current_pos, char *input_str, char c)
{
	int	i;

	if (input_str == NULL)
		return ;
	i = 0;
	// TODO - Jo: check if +1 necessary here
	while (i < 3 && input_str[*current_pos + 1] && input_str[*current_pos
		+ 1] == c)
	{
		(*current_pos)++;
		i++;
	}
}

// TODO -Jo : idem, check if +1 necessary
void	word_token(int *current_pos, char *input_str, char c)
{
	while (input_str[*current_pos + 1] && get_token_hint(input_str[*current_pos
			+ 1]) == get_token_hint(c))
		(*current_pos)++;
}
