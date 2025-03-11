
#include "../include/minishell.h"

t_msh_state fn_msh_parser(t_minishell *mshell)
{
    execute_commands(mshell->commands);
}