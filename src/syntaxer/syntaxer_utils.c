#include "minishell.h"

// Checks PIPE syntax:
// Two pipe symbols are not allowed
// A pipe should be followed by a command
// A pipe can not be first or last in the input string
int	pipe_syntaxer(t_token *prev_token, t_token *curr_token)
{
	t_token	*next_token;

	if (!curr_token || !curr_token->str)
		return (1);
	if (ft_strlen(curr_token->str) != 1)
		return (1);
	next_token = skip_space_token(curr_token);
	if (prev_token == NULL || next_token == NULL)
		return (1);
	if ((ft_strncmp(prev_token->str, "|", 1) == 0)
		&& (ft_strncmp(curr_token->str, "|", 1) == 0))
		if ((ft_strncmp(curr_token->str, "|", 1) == 0)
			&& (ft_strncmp(next_token->str, "|", 1) == 0))
			return (1);
	if (next_token->type != WORD)
		return (1);
	return (0);
}

// Checks if the quote is closed.
int	quote_syntaxer(t_token *prev_token, t_token *curr_token)
{
	int	i;
	int	len;

	if (!curr_token || !curr_token->str)
		return (1);
	i = 0;
	len = ft_strlen(curr_token->str) - 1;
	if (curr_token->str[i] != curr_token->str[len])
		return (1);
	return (0);
}

// Checks if the syntax for words is respected
// TODO: for now this check is basic (null, empty string, forbidden characters)
// but let's see if we can add more cases for it.
int	word_syntaxer(t_token *prev_token, t_token *curr_token)
{
	if (!curr_token || !curr_token->str)
		return (1);
	if ((ft_strncmp(curr_token->str, ";", 1) == 0)
		|| (ft_strncmp(curr_token->str, "\\", 1) == 0))
		return (1);
	return (0);
}

int	redir_syntaxer(t_token *prev_token, t_token *curr_token)
{
	t_token	*next_token;

	if (!curr_token || !curr_token->str)
		return (1);
	next_token = skip_space_token(curr_token);
	if (!next_token)
		return (1);
	if (ft_strlen(curr_token->str) > 2)
		return (1);
	if (next_token->type != S_QUOTE || next_token->type != D_QUOTE
		|| next_token->type != WORD)
		return (1);
	return (0);
}

// Placeholder function (for tokens which syntax' you can not check)
int	na_syntaxer(t_token *prev_token, t_token *curr_token)
{
	(void)prev_token;
	(void)curr_token;
	return (0);
}

int	env_syntaxer(t_token *prev_token, t_token *curr_token)
{
	t_token *next_token;

	if (!curr_token || !curr_token->str)
		return (1);
	if (!ft_isalpha(curr_token->str[1]) && (curr_token->str[1]) != '?')
		return (1);
	return (0);
}