
#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include "lexer.h"

void					init_env(char **envp, t_envs *envs);
int						expand_env(t_token *list_tokens, t_envs *envs);
char					*extract_env(char *str, t_envs *envs, size_t len);
t_env_node				*create_new_env_node(char *var, char *value);
void					add_env_to_list(t_env_node **list, t_env_node *node);
#endif