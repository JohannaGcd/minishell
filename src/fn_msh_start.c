
#include "../include/minishell.h"

t_msh_state fn_msh_start(t_minishell *mshell, char **envp)
{
    t_envs		*env;
    env = (t_envs *)malloc(sizeof(t_envs));

    printf("debug START\n");
	if (env == NULL)
	{
		perror("Failed to allocate memory for envs");
		return (MSH_EXIT);
	}
	init_env(envp, env);
    mshell->envs = env;
    mshell->input_str = NULL;
    mshell->commands = NULL;
    mshell->tokens = NULL;
    return (MSH_READLINE);
}

t_msh_state fn_msh_readline(t_minishell *mshell)
{
    const char prompt[] = "minishell > ";

    printf("debug READLINE\n");
    mshell->input_str = readline(prompt);
    if (!mshell->input_str)
        return (MSH_CLEAN);
    if (*mshell->input_str)
        add_history(mshell->input_str);
    return (MSH_LEXER);
}
