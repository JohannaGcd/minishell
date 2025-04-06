#include "../include/minishell.h"
#include "../include/executer.h"

t_msh_state fn_msh_executer(t_minishell *mshell)
{
    printf("debug EXECUTER\n");
    execute_commands(mshell);
    return(MSH_READLINE);
}