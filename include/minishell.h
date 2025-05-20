/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:10 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/19 14:12:59 by jguacide      ########   odam.nl         */
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
# include <signal.h>

extern volatile sig_atomic_t signal_received;

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

typedef enum e_type_red
{
	RED_OUT,
	RED_IN,
	APPEND,
	HEREDOC,
}	t_type_red;

typedef struct s_redirection
{
	t_type_red				type;
	char					*file;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

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
	int			isExit;
	char		*pwd;
	char		*old_pwd;
}	t_minishell;

typedef enum e_signal
{
	MAIN_SIG,
	CHILD_SIG,
	PARENT_SIG,
	HEREDOC_SIG,
}	t_signal;

typedef struct s_pipe_io
{
	int	pipe_fd[2];
	int	prev_read_end;

}	t_pipe_io;

typedef t_msh_state	(*t_msh_function)(t_minishell *mshell, int *exit_status);

t_msh_state		mshell_start(t_minishell *mshell, char **envp);
t_msh_state		mshell_readline(t_minishell *mshell, int *exit_status);
t_msh_state		mshell_lexer(t_minishell *mshell, int *exit_status);
t_msh_state		mshell_syntaxer(t_minishell *mshell, int *exit_status);
t_msh_state		mshell_parser(t_minishell *mshell, int *exit_status);
t_msh_state		mshell_executer(t_minishell *mshell, int *exit_status);
t_msh_state		mshell_clean(t_minishell *mshell, int *exit_status);
void			handle_signal(int mode);
void			clean_commands(t_command *commands);

#endif