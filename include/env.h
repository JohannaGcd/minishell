#ifndef ENV_H
# define ENV_H

# include "lexer.h"
# include "minishell.h"
# include "minishell.h"

typedef struct s_env_node
{
	char				*var;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_envs
{
	t_env_node			*env;
	int					status;
}						t_envs;

void					init_env(char **envp, t_envs *envs);
int						expand_env(t_token *list_tokens, t_envs *envs);
char					*extract_env(char *str, t_envs *envs, size_t len);

#endif