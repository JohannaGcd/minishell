#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_token_type
{
	TOKEN,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT,
	WORD,
	M_SPACE,
	ENV,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}					t_token;

// lexer.c
t_token				*extract_tokens(char *input_str);
void				fill_token_info(int *current_pos, char *input_str,
						t_token *new_token);
int					get_token_hint(char c);

// lexer_list_utils.c
t_token				*token_list_find_last(t_token *token_list_node);
void				token_list_add_back(t_token **token_list_head,
						t_token *new_token);
t_token				*create_new_token(void);

// lexer_utils.c
void				pipe_token(int *current_pos, char *input_str, char c);
void				space_token(int *current_pos, char *input_str, char c);
void				quote_token(int *current_pos, char *input_str, char c);
void				redirect_token(int *current_pos, char *input_str, char c);
void				word_token(int *current_pos, char *input_str, char c);
void				env_token(int *current_pos, char *input_str, char c);
int					ft_isspace(char c);

#endif