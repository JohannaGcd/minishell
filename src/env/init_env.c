#include "../../include/minishell.h"

t_env_node *create_new_env_node (char *var, char*value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		return (NULL);
	node->value = ft_substr(value, 0 , ft_strlen(value));
	node->var = ft_substr(var, 0 , ft_strlen(var));
	node->next = NULL;
	return (node);
}

void add_env_to_list(t_env_node *list, t_env_node	*node)
{
	t_env_node *tmp;
	tmp = list;

	list = node;
	node->next = tmp;
}
void init_env(char **envp, t_envs *envs)
{
	int	i;
	char	*var;
	char	*value;
	int j;
	t_env_node *node;

	i = 0;
	
	envs->status = 0;
	envs->env = NULL;
	while (envp[i])
	{
		j = 0;
		while (j < ft_strlen(envp[i]))
		{
			if(envp[i][j] == '=')
			{
				var = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				//printf("%s, %s\n", var, value);
				node = create_new_env_node(var, value);
				//printf("node created\n");
				add_env_to_list(envs->env, node);
				//printf("added list\n");
				free(var);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}