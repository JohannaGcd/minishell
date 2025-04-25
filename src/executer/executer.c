/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/25 15:16:18 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_multiple_cmd(t_command *command)
{
	// fork
	// pipe
	// redirect -> output of first command goes to second one
	int pipe_fd[2];
	pid_t pid = fork();
	if ((pipe_fd) == -1)
	{
		perror("Error with pipe in execute_multiple_cmd");
		return -1;
	}

	else if (pid == 0)
	{
		io_redirect(command); // change for multiple cmds? how? get last one?

	}
	else
	{
		// what happens in Parent vs child?
		int status;
		waitpid(pid, &status, 0);
	}
}


void	execute_single_cmd(t_command *command)
{
	if (command->in) //TODO: find a way to only call if a heredoc. use a flag.
		handle_heredoc(&command);
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
        // Child process
		io_redirect(command);
		//retrieve_cmds();
		if (execvp(command->command_args[0], command->command_args) == -1)
		{
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    } 
	else 
	{
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int is_builtin_command(char **command_args)
{
	if (ft_strncmp(command_args[0],"export", 7) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"env", 4) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"unset", 6) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"exit", 5) == 0)
		return (1);
	if (ft_strncmp(command_args[0],"cd", 3) == 0)
		return (1);
	return (0);
}

void execute_builtin(char **command_args, t_minishell *mshell)
{
	if (ft_strncmp(command_args[0],"export", 7) == 0)
		exec_export(command_args, mshell);
	else if (ft_strncmp(command_args[0],"env", 4) == 0)
		exec_env(mshell);
	else if (ft_strncmp(command_args[0],"unset", 6) == 0)
		exec_unset(command_args, mshell);
	else if (ft_strncmp(command_args[0],"exit", 5) == 0)
		exec_exit(command_args, mshell);
}

void execute_commands(t_minishell *mshell) 
{
	t_command   *current;
	current = mshell->commands;
	
	while (current) 
	{  
		printf("debug current command %s\n", current->command_args[0]); 
		if (is_builtin_cmd(current->command_args))
			execute_builtin(current->command_args, mshell);
		else if (current->next == NULL)
			execute_single_cmd(current);
		else
			execute_multiple_cmd(current);
		current = current->next;
	}
}
