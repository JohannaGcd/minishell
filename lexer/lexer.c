#include "../include/minishell.h"

// To set the type of the token based on the first character.
int	get_token_hint(char c)
{
	char	set_type[] = {'-', '|', '\'', '\"', '<', '>'};
	int		value;

	value = 0;
	while (value < 6)
	{
		if (c == set_type[value])
			break ;
		value++;
	}
	return (value);
}

// To fill the token node, with its type and the corresponding character string
void	fill_token_info(int *current_pos, char *input_str, t_token *new_token)
{
	int	start_pos;

	start_pos = *current_pos;
	new_token->type = get_token_hint(input_str[*current_pos]);
	void (*get_full_token[])(int *, char *, char) = {
		[TOKEN] = NULL,
		[PIPE] = pipe_token,
		[S_QUOTE] = quote_token,
		[D_QUOTE] = quote_token,
		[REDIRECT_IN] = redirect_token,
		[REDIRECT_OUT] = redirect_token,
		[WORD] = word_token,
	};
	get_full_token[new_token->type](current_pos, input_str,
		input_str[*current_pos]);
	new_token->str = ft_substr(input_str, start_pos, ((*current_pos - start_pos)
				+ 1));
}

// To extract the complete list of tokens from the input string
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