/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/20 15:17:48 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute_single_command(t_command *command)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) 
	{
        // Child process
        open_file_redirect(command);
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
        // printf("in execute single command: redirect in is: %d with file %s\n", command->in->type, command->in->file);
        // printf("in execute single command: redirect out is: %d with file %s\n", command->out->type, command->out->file);
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
		if (is_builtin_command(current->command_args))
			execute_builtin(current->command_args, mshell);
		else
			execute_single_command(current);
		current = current->next;
	}
}
