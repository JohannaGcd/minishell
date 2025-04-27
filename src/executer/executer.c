/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/27 16:14:31 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_multiple_cmd(t_command **command, char **envp, t_minishell *mshell)
{
	// fork
	// pipe
	// redirect -> output of first command goes to second one
	int pipe_fd[2];
	pid_t id_array[2];
	char *command_wp;
	if (pipe(pipe_fd) == -1)
	{
		perror("Error with pipe in execute_multiple_cmd");
		return -1;
	}
	// Fork first child
	id_array[0] = fork();
	if (id_array[0] == -1)
		return (perror("error forking first child process"), EXIT_FAILURE);
	
	// Child process 1
	if (id_array[0] == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect STDOUT to pipe write-end
		close(pipe_fd[0]); //close unused read end
		close(pipe_fd[1]); // close write end after dup2;
		io_redirect(*command); // apply normal redirections if any
		command_wp = return_command_with_path((*command)->command_args[0], mshell);
		printf("\n1: %s\n", command_wp);
		if (execve((*command)->command_args[0], (*command)->command_args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
	}
	// Fork second child
	id_array[1] = fork();
	if (id_array[1] == -1)
		return (perror("error forking second child process"), EXIT_FAILURE);
	// Child process 2
	if (id_array[1] == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		io_redirect((*command)->next);
		command_wp = return_command_with_path((*command)->next->command_args[0], mshell);
		printf("\n2: %s\n", command_wp);
		if (execve((*command)->next->command_args[0], (*command)->next->command_args, envp) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
	}
	else
	{
		// what happens in Parent vs child?
		int status1;
		int status2;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(id_array[0], &status1, 0);
		waitpid(id_array[1], &status2, 0);
	}
	return (0);
}

void	execute_single_command(t_command *command, char **envp)
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
		if (execve(command->command_args[0], command->command_args, envp) == -1)
        {
            perror("execve failed");
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

int is_builtin_cmd(char **command_args)
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
	char		**envp;
	char		*command_wp;

	current = mshell->commands;
	mshell->envs->status = 0;
	while (current) 
	{  
		printf("debug current command %s\n", current->command_args[0]); 
		if (is_builtin_cmd(current->command_args))
			execute_builtin(current->command_args, mshell);
		else if (current->next == NULL)
		{
			envp = envs_to_envp(mshell->envs);
			command_wp = return_command_with_path(current->command_args[0], mshell);
			if (command_wp)
				current->command_args[0] = command_wp;
			else
			{
				printf("minishell: %s : command not found\n", current->command_args[0]);
				mshell->envs->status = 127;
				return;
			}
			printf("command with path =%s\n", current->command_args[0]);
			execute_single_command(current, envp);
			free_array(envp);
		}
		else
		{
			envp = envs_to_envp(mshell->envs);
			execute_multiple_cmd(&mshell->commands, envp, mshell);
			break;
		}
		break;
		// current = current->next;
	}
}
