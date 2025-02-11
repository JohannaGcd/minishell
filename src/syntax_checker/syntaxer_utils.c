#include "minishell.h"

void	pipe_syntaxer(char *token_str)
{
	int i = 0;
	if (token_str[i] == '|')
	{
		write(1, "YES", 3);
	}
}