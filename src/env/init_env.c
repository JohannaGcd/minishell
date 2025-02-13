#include "../../include/minishell.h"

void init_env(char **envp, t_envs *envs)
{
	int	i;
	char	*var;
	char	*value;
	int j;

	i = 0;
	
	envs->status = 0;
	while (envp[i])
	{
		j = 0;
		while (j < ft_strlen(envp[i]))
		{
			if(envp[i][j] == '=')
			{
				var = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);

				free(var);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}