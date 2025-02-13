#include "../../include/minishell.h"

int init_env(char **envp, t_envs *envs)
{
	int	i;
	int	var;
	int	value;

	i = 0;
	envs->status = 0;
	while (envp[i])
	{
		i++;
	}
}