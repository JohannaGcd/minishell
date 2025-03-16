#ifndef EXECUTER_H
# define EXECUTER_H
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "env.h"
# include "minishell.h"

void execute_commands(t_command *commands);
void handle_exe_redirections(t_command *command);
void execute_single_command(t_command *command);
int is_builtin_command(char **command_args);
void execute_builtin(char **command_args);
void restore_file_descriptors(int saved_stdin, int saved_stdout);

#endif