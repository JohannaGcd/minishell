/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:21:54 by jguacide      #+#    #+#                 */
/*   Updated: 2025/04/15 15:41:13 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void open_file_redirect(t_command *command)
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
        //printf("red_out while loop\n");
        int out_fd;
        if (red_out->type == APPEND) {
            printf("append: %s\n", red_out->file);
            out_fd = open(red_out->file, O_WRONLY | O_CREAT | O_APPEND);
        }
        else {
            //printf("trunc: %s\n", red_out->file);
            out_fd = open(red_out->file, O_WRONLY | O_CREAT | O_TRUNC);
        }
        if (out_fd == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO); // Redirect stdout
        close(out_fd);
        red_out = red_out->next;
    }
}

// HEREDOC NOTES:
// cmd (args) << delimeter
// blabla
// delimiter
// reads until delimiter and feeds into pipe, then sends to the commands. 