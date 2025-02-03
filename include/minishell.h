#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h> // for testing!
# include <stdlib.h>
# include <unistd.h>

// PART 1: DATA STRUCTURES

// Tokenisation

// Parsing

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

// Tokenisation

// Parsing

#endif