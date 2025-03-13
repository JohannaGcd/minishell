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
    t_token *tmp;

    tokens = extract_tokens(string);
    if (ft_strncmp(tokens->str,"ls", 2) != 0 || tokens->type != WORD)
        return (0);
    if (!tokens->next)
        return (0);
    tmp = tokens->next;
    if (ft_strncmp(tmp->str,"-la", 3) != 0 || tokens->type != WORD)
        return (0);
    if (!tokens->next)
        return (0);
}

int test_lexer_quotes()
{
    char    *string1 = "echo 'HELLO WORLD'";
    char    *sytring2 = "echo \"HELLO WORLD\"";
}