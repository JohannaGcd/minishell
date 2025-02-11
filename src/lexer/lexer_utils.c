#include "../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ');
}

// To extract a pipe token
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

// To extract a single or double quote token
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

void	env_token(int *current_pos, char *input_str, char c)
{
	if (input_str == NULL)
		return ;
	(*current_pos)++; 
	if (input_str[*current_pos] && input_str[*current_pos] == '?')
	{
		(*current_pos)++;
		return ;
	}
	if (input_str[*current_pos] && (ft_isalpha(input_str[*current_pos]) || input_str[*current_pos] == '_'))
		(*current_pos)++;
	while (input_str[*current_pos] && ft_isalpha(input_str[*current_pos]))
		(*current_pos)++;
}

// To extract a redirection token
void	redirect_token(int *current_pos, char *input_str, char c)
{
	int	i;

	if (input_str == NULL)
		return ;
	i = 0;
	while (i < 3 && input_str[*current_pos] && input_str[*current_pos] == c)
	{
		(*current_pos)++;
		i++;
	}
}

// To extract a word token
void	word_token(int *current_pos, char *input_str, char c)
{
	while (input_str[*current_pos]
		&& get_token_hint(input_str[*current_pos]) == get_token_hint(c))
		{
		(*current_pos)++;
		}
}

void space_token(int *current_pos, char *input_str, char c)
{
	while (input_str[*current_pos] && ft_isspace(input_str[*current_pos]))
    {
        (*current_pos)++;
    }
}
