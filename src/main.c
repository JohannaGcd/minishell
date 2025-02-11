#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int i;
	char *input_str;
	const char prompt[] = "minishell > ";
	t_token *test;
	t_token *tmp;

	//prompt = "minishell > ";
	while (1)
	{
	input_str = readline(prompt);
	test = extract_tokens(input_str);

	tmp = test;
	i = 0;
	while (tmp != NULL)
	{
		printf("token%d:<%s>\n", i, tmp->str);
		i++;
		tmp = tmp->next;
	}
	expand_env(test);
	}
	return (0);
}