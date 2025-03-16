#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "env.h"
# include "lexer.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h> // for testing!
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// TODO: HANDLE ERRORS.
// -> for now we "return 1" in case of error, but we should
// define what number to send depending on the type of error we face
// and define the appropriate behavior for each type of error

// PART 1: DATA STRUCTURES

// Lexical Analyser (ie. Lexer)

// Parser
typedef enum s_msh_state
{
	MSH_START,
	MSH_READLINE,
	MSH_LEXER,
	MSH_SYNTAXER,
	MSH_PARSER,
	MSH_EXECUTER,
	MSH_CLEAN,
	MSH_EXIT
}	t_msh_state;

typedef enum	e_type_red
{
	RED_OUT,
	RED_IN,
	APPEND,
	HEREDOC,
} t_type_red;

typedef struct s_redirection
{
	t_type_red			type;
	char				*file;
	int					fd;
	struct s_redirection		*next;
}						t_redirection;

// typedef struct s_retd_out
// {
// 	t_type_red	type;
// 	char *filename;
// 	void *next;
// };


typedef struct s_command
{
	char				**command_args;
	t_redirection		*in;
	t_redirection		*out;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	t_envs		*envs;
	char		*input_str;
	t_token		*tokens;
	t_command	*commands;
}	t_minishell;

typedef t_msh_state (*t_msh_function)(t_minishell *mshell); 

// PART 2: FUNCTION DEFINITIONS

// Lexical Analysis
// -> Separates the input into tokens

// lexer.c
t_token					*extract_tokens(char *input_str);
void					fill_token_info(int *current_pos, char *input_str,
							t_token *new_token);
int						get_token_hint(char c);

// lexer_list_utils.c
t_token					*token_list_find_last(t_token *token_list_node);
void					token_list_add_back(t_token **token_list_head,
							t_token *new_token);
t_token					*create_new_token(void);

// lexer_utils.c
void					pipe_token(int *current_pos, char *input_str, char c);
void					space_token(int *current_pos, char *input_str, char c);
void					quote_token(int *current_pos, char *input_str, char c);
void					redirect_token(int *current_pos, char *input_str,
							char c);
void					word_token(int *current_pos, char *input_str, char c);
void					env_token(int *current_pos, char *input_str, char c);
int						ft_isspace(char c);

// Syntax Checker
// -> Checks whether the tokens respect grammar rules for BASH

// syntaxer.c
int						syntaxer(t_token *token_list);
int						check_token_syntax(t_token *prev_token,
							t_token *curr_token);
t_token					*skip_space_token(t_token *current_token);

// syntaxer_utils.c
int						pipe_syntaxer(t_token *prev_token, t_token *curr_token);
int						quote_syntaxer(t_token *prev_token,
							t_token *curr_token);
int						word_syntaxer(t_token *prev_token, t_token *curr_token);
int						redir_syntaxer(t_token *prev_token,
							t_token *curr_token);
int						na_syntaxer(t_token *prev_token, t_token *curr_token);
int						env_syntaxer(t_token *prev_token, t_token *curr_token);

// Parsing
// -> Processes the tokens according to a grammar and builds the command structs

// parser.c
t_command				*extract_commands(t_token *token_list);
t_command				*init_command(void);
void					fill_command(t_command **new_command,
							t_token *token_list);
void					get_command_args(t_command **new_command,
							t_token *token_list);

//functions
t_msh_state fn_msh_start(t_minishell *mshell, char **envp);
t_msh_state fn_msh_readline(t_minishell *mshell);
t_msh_state fn_msh_lexer(t_minishell *mshell);
t_msh_state fn_msh_syntaxer(t_minishell *mshell);
t_msh_state fn_msh_parser(t_minishell *mshell);
t_msh_state fn_msh_executer(t_minishell *mshell);
t_msh_state fn_msh_clean(t_minishell *mshell);
#endif