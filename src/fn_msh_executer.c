#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state fn_msh_executer(t_minishell *mshell)
{
    execute_commands(mshell->commands);
    return(MSH_READLINE);
}