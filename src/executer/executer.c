/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/07 23:04:27 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"
#include "../include/env.h"

void handle_exe_redirections(t_command *command)
{
    t_redirection *red_in;
    t_redirection *red_out;
    
    red_in = command->in;
    while (red_in)
	{
        int in_fd = open(red_in->file, O_RDONLY);
        if (in_fd == -1) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO); // Redirect stdin
        close(in_fd);
        red_in = red_in->next;
    }
    red_out = command->out;
    while (red_out)
	{
        int out_fd = open(red_out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO); // Redirect stdout
        close(out_fd);
        red_out = red_out->next;
    }
}

void execute_single_command(t_command *command)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
	else if (pid == 0) 
	{
        // Child process
        handle_exe_redirections(command);
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

void exec_export_print(t_minishell *mshell)
{
    t_env_node	*node;

    node = mshell->envs->env;
    while (node)
    {
    printf("declare -x %s=\"%s\"\n",node->var, node->value);
    node = node->next;
    }
}

void exec_export(t_command *command, t_minishell *mshell)
{
    //add env
    int count;
    char *var;
    char *value;
    t_env_node	*node;
    

    count = 0;
    while(command->command_args[count])
        count++;
    if (count == 1)
        exec_export_print(mshell);
    else if (count == 2)
    {
        var = ft_substr(command->command_args[1], 0, ft_strchr(command->command_args[1], '=') - command->command_args[1]);
		value = ft_substr(command->command_args[1],
				(ft_strchr(command->command_args[1], '=') - command->command_args[1]) + 1, ft_strlen(command->command_args[1]));
                node = create_new_env_node(var, value);
                add_env_to_list(&(mshell->envs->env), node);
    }
     else if (count == 3)
    {
        var = ft_substr(command->command_args[1], 0, ft_strchr(command->command_args[1], '=') - command->command_args[1]);
		value = ft_substr(command->command_args[2], 0, ft_strlen(command->command_args[2]));
        node = create_new_env_node(var, value);
        add_env_to_list(&(mshell->envs->env), node); 
    }
    
    
}

void execute_commands(t_minishell *mshell) 
{
	t_command   *current;
    current = mshell->commands;
    
	while (current) 
	{   
        if (ft_strncmp(current->command_args[0],"export", 7) == 0)
        {
            exec_export(current, mshell);
        }
        else
		    execute_single_command(current);
		current = current->next;
	}
}
