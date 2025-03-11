#include "../include/minishell.h"

t_msh_state fn_msh_lexer(t_minishell *mshell)
{
    mshell->tokens = extract_tokens(mshell->input_str);
}

t_msh_state fn_msh_syntaxer(t_minishell *mshell)
{
    syntaxer(mshell->tokens);
}

t_msh_state fn_msh_parser(t_minishell *mshell)
{
    mshell->commands = extract_commands(mshell->tokens);
}