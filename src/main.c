#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int i;
	char *input_str;
	const char prompt[] = "minishell > ";
	t_token *test;
	t_token *tmp;

	// prompt = "minishell > ";
	t_envs *envs;
	t_env_node *tmp_node;

	envs = (t_envs *)malloc(sizeof(t_envs));
	init_env(envp, envs);
	printf("env inited\n");
	tmp_node = envs->env;
	while (tmp_node)
	{
		printf("value=%s\n", tmp_node->value);
		printf("var=%s\n", tmp_node->var);
		tmp_node = tmp_node->next;
	}
	while (1)
	{
		input_str = readline(prompt);
		test = extract_tokens(input_str);

		tmp = test;
		i = 0;
		while (tmp != NULL)
		{
			printf("token %d:<%s>\n", i, tmp->str);
			i++;
			tmp = tmp->next;
		}
		return (0);
	}