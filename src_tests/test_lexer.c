# include "../include/minishell.h"
#include "../include/minishell.h"

int test_lexer_one_command()
{
	char    *string1 = "more";
	t_token	*tokens;
	
	tokens = extract_tokens(string1);
	if (ft_strncmp(tokens->str,"more", 4) != 0 || tokens->type != WORD)
		return (0);
	if (tokens->next)
		return (0);
	return (1);
	free(tokens);
}

int test_lexer_one_command_and_param()
{
	char    *string = "ls -la";
	t_token	*tokens;

	tokens = extract_tokens(string);
	if (ft_strncmp(tokens->str,"ls", 2) != 0 || tokens->type != WORD)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if(tokens->type != M_SPACE)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if (ft_strncmp(tokens->str,"-la", 3) != 0 || tokens->type != WORD)
		return (0);
	if (tokens->next)
		return (0);
	return (1);
}

int test_lexer_single_quotes()
{
	char    *string = "echo 'HELLO WORLD'";

	t_token	*tokens;

    tokens = extract_tokens(string);
	if (ft_strncmp(tokens->str,"echo", 4) != 0 || tokens->type != WORD)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if(tokens->type != M_SPACE)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if (ft_strncmp(tokens->str,"'HELLO WORLD'", 14) != 0 || tokens->type != S_QUOTE)
		return (0);
	if (tokens->next)
		return(0);
	return(1);
}

int test_lexer_double_quotes()
{
   char    *string = "echo \"HELLO WORLD\"";
   t_token	*tokens;

    tokens = extract_tokens(string);
	if (ft_strncmp(tokens->str,"echo", 4) != 0 || tokens->type != WORD)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if(tokens->type != M_SPACE)
		return (0);
	if (!tokens->next)
		return (0);
	tokens = tokens->next;
	if (ft_strncmp(tokens->str,"\"HELLO WORLD\"", 14) != 0 || tokens->type != D_QUOTE)
		return (0);
	if (tokens->next)
		return(0);
   return(1);
}

int test_with_print()
{
   char    *string = "ls > file1 >> file2 < file3 << file4";
   t_token	*tokens;

    tokens = extract_tokens(string);
	while(tokens)
	{
		printf("token=<%s>, type=%u\n",tokens->str, tokens->type);
		tokens = tokens->next;
	}
	return(0);
}
