#include "../include/minishell.h"

t_msh_state fn_msh_clean(t_minishell *mshell)
{
	if (mshell->input_str)
		free(mshell->input_str);
	if (mshell->tokens)
		free(mshell->tokens);
	if (mshell->commands)
		free(mshell->commands);
	if (mshell->envs)
		free(mshell->envs);
	return (MSH_EXIT);
}