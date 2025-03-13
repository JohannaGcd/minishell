#include "../include/minishell.h"

t_msh_state fn_msh_lexer(t_minishell *mshell)
{
    mshell->tokens = extract_tokens(mshell->input_str);
    if (mshell->tokens == NULL)
        return (MSH_CLEAN);
    return (MSH_SYNTAXER);
}

t_msh_state fn_msh_syntaxer(t_minishell *mshell)
{
    if (syntaxer(mshell->tokens))
        return (MSH_READLINE);
    else
        return (MSH_PARSER);
}
}

t_msh_state fn_msh_parser(t_minishell *mshell)
{
    mshell->commands = extract_commands(mshell->tokens);
    if (mshell->commands == NULL)
        return (MSH_CLEAN);
    return (MSH_EXECUTER);
}