/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:10 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/26 10:40:10 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
}			t_envs;

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
	int 		isExit;
}	t_minishell;

typedef enum e_signal
{
	MAIN_SIG,
	CHILD_SIG,
	PARENT_SIG,
	HEREDOC_SIG,
}	t_signal;

typedef t_msh_state (*t_msh_function)(t_minishell *mshell); 

// PART 2: FUNCTION DEFINITIONS

// Lexical Analysis
// -> Separates the input into tokens

//functions
t_msh_state		mshell_start(t_minishell *mshell, char **envp);
t_msh_state		mshell_readline(t_minishell *mshell);
t_msh_state 	mshell_lexer(t_minishell *mshell);
t_msh_state 	mshell_syntaxer(t_minishell *mshell);
t_msh_state 	mshell_parser(t_minishell *mshell);
t_msh_state 	mshell_executer(t_minishell *mshell);
t_msh_state 	mshell_clean(t_minishell *mshell);
void			handle_signal(int mode);
#endif