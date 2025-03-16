#include "../include/minishell.h"

t_msh_state fn_msh_lexer(t_minishell *mshell)
{
    printf("LEXER\n");
    mshell->tokens = extract_tokens(mshell->input_str);
    if (mshell->tokens == NULL)
        return (MSH_CLEAN);
    //expand_env(mshell->tokens, mshell->envs);
    //check that expand sucessful
    return (MSH_SYNTAXER);
}

t_msh_state fn_msh_syntaxer(t_minishell *mshell)
{
    printf("SYNTAXER\n");
    if (syntaxer(mshell->tokens))
    {
        if (mshell->input_str)
		    free(mshell->input_str);
	    if (mshell->tokens)
        {
            //write function to clean list
		    free(mshell->tokens);
        }
        return (MSH_READLINE);
    }
    else
        return (MSH_PARSER);
}


t_msh_state fn_msh_parser(t_minishell *mshell)
{
    printf("PARSER\n");
    mshell->commands = extract_commands(mshell->tokens);
    if (mshell->commands == NULL)
        return (MSH_CLEAN);
    return (MSH_EXECUTER);
}