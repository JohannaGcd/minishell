/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:14 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/25 14:53:43 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */




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
# include "lexer.h"
# include "minishell.h"
#include <limits.h>

void	execute_commands(t_minishell *mshell);
void	io_redirect(t_command *command);
void	execute_single_cmd(t_command *command);
void	exec_export(char **command_args, t_minishell *mshell);
void	exec_env(t_minishell *mshell);
void	exec_unset(char **command_args, t_minishell *mshell);
int		is_builtin_cmd(char **command_args);
void	execute_builtin(char **command_args, t_minishell *mshell);
int 	exec_exit(char **command_args, t_minishell *mshell);
void execute_multiple_cmd(t_command *command);

void restore_file_descriptors(int saved_stdin, int saved_stdout);

void handle_heredoc(t_command **command);
int read_heredoc(char *delimiter);

#endif