#ifndef ENV_H
# define ENV_H

typedef struct s_env_node
{
	char    *var;
	char    *value;
	s_env_node *next;
}   t_env_node;

typedef struct s_envs
{
	t_env_node	*env;
	int			status;
}
#endif