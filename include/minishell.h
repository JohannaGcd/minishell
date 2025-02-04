#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h> // for testing!
# include <stdlib.h>
# include <unistd.h>

// PART 1: DATA STRUCTURES

// Lexical Analyser (ie. Lexer)

typedef enum s_token_type
{
	TOKEN,
	PIPE,
	IS_SPACE,
	S_QUOTE,
	D_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT,
	WORD,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	struct s_token		*next;
}						t_token;

// Parser

typedef struct s_redirection
{
	char				*file;
	int					fd;
}						t_redirection;

typedef struct s_command
{
	char				**command_args;
	t_redirection		*in;
	t_redirection		*out;
	struct s_command	*next;
}						t_command;

// PART 2: FUNCTION DEFINITIONS

// Lexical Analysis
// -> Separates the input into tokens

// lexer_list_utils.c
t_token					*token_list_find_last(t_token *token_list_node);
void					token_list_add_back(t_token **token_list_head,
							t_token *new_token);
t_token					*create_new_token(void);

// lexer.c

// Parsing
// -> Processes the tokens according to a grammar and builds the command structs

#endif