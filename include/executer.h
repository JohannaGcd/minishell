/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:14 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/26 13:25:09 by jguacide      ########   odam.nl         */
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
# include <limits.h>
# include <stdbool.h>

void	execute_commands(t_minishell *mshell, int *exit_status);
int		io_redirect(t_command *command, t_minishell *mshell);
int		execute_if_single_command(t_command *cmd, t_minishell *mshell);
int		execute_single_command(t_minishell *mshell, t_command *command,
			char **envp);
void	exec_export(char **command_args, t_minishell *mshell);
void	exec_env(char **command_args, t_minishell *mshell);
void	exec_unset(char **command_args, t_minishell *mshell);
void	exec_pwd(char **command_args, t_minishell *mshell);
void	exec_cd(char **command_args, t_minishell *mshell);
void	exec_echo(char **command_args, t_minishell *mshell);
int		is_builtin_cmd(char **command_args);
void	redirect_for_builtin(t_command *cmd, t_minishell *mshell,
			int *exit_status);
void	execute_builtin(char **command_args, t_minishell *mshell,
			int *exit_status);
int		exec_exit(char	**command_args, t_minishell	*mshell,
			int	*exit_status);
int		execute_multiple_cmd(t_minishell *mshell,
			int *exit_status);
void	wait_for_children(t_minishell *mshell, pid_t child_id,
			int nbr_children);
char	**prep_env_and_path(t_minishell *mshell, t_command *current);
char	*return_cmd_w_path(char *command, t_minishell *mshell);
int		execute_last_cmd(t_minishell *mshell, t_command *curr_cmd,
			t_pipe_io *pipe_io, int *exit_status);
int		update_pipe_fd(t_pipe_io *pipe_io);
void	free_array(char **args);
int		execute_child(t_minishell *mshell, t_command *curr_cmd,
			t_pipe_io *pipe_io, int *exit_status);
void	handle_heredoc(t_minishell *mshell, t_command **command);
int		read_heredoc(char *delimiter);
int		number_arguments(char **command_args);
bool	set_all_heredocs(t_minishell *mshell);
void	set_or_update_env(t_minishell *mshell, char *var, char *value);
void	init_pipe_io(t_pipe_io *pipe_io);
void	execute_pipeline(t_minishell *mshell, int *exit_status,
			int *nbr_children, t_pipe_io *pipe_io);
void	setup_last_child_io(int prev_read_end);
void	write_line_to_pipe(int pipe_fd, char *line);
int		setup_heredoc_pipe(void);
int		process_heredoc_input(int write_fd, char *delimiter);
void	set_up_child_fds(t_pipe_io *pipe_io);
void	handle_builtin(t_command *curr_cmd, t_minishell *mshell,
			int *exit_status);
void	exec_export_print(t_minishell *mshell);
int		equal_in_mid(char *str);
int		equal_is_last(char *str);
void	not_valid(char *str, t_minishell *mshell);
#endif