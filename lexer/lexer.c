#include "../include/minishell.h"

void	fill_token(void);

t_token	*extract_tokens(char *input_str)
{
	t_token	*token_list_head;
	t_token	*new_token;
	int		current_pos;

	token_list_head = NULL;
	current_pos = 0;
	while (input_str[current_pos] != '\0')
	{
		new_token = create_new_token();
		fill_token_info(&current_pos, input_str, new_token);
		token_list_add_back(&token_list_head, new_token);
		current_pos++;
	}
	return (token_list_head);
}

int	main(void)
{
	int i;
	char *input_str;
	char *prompt;
	t_token *test;
	t_token *tmp;

	prompt = "minishell > ";
	input_str = readline(prompt);
	test = extract_token(input_str);

	tmp = test;
	i = 0;
	while (tmp != NULL)
	{
		printf("token %d: %s \n", i, tmp->str);
		i++;
		tmp = tmp->next;
	}
	return (0);
}