/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:21:54 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/08 15:21:57 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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