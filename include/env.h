#ifndef ENV_H
# define ENV_H

typedef struct s_env_node
{
	char    	*var;
	char    	*value;
	struct s_env_node	*next;
}   t_env_node;

typedef struct s_envs
{
	t_env_node	*env;
	int			status;
} 	t_envs;

void init_env(char **envp, t_envs *envs);
#endif