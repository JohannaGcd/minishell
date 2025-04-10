/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 13:52:31 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/10 17:15:05 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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
