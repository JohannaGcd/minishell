/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:21:54 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/13 15:34:12 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void io_redirect(t_command *command)
{
    t_redirection *red_in;
    t_redirection *red_out;
    
    red_in = command->in;
    while (red_in)
    {
        // if (red_in->type != HEREDOC)
        // {
        //     command->in->fd = open(red_in->file, O_RDONLY);
        //     if (command->in->fd == -1) {
        //         perror("Error opening input file");
        //         exit(EXIT_FAILURE);
        //     }
        // }
        // dup2(command->in->fd, STDIN_FILENO);
        
        // close(command->in->fd);
        red_in = red_in->next;
    }

    red_out = command->out;
    while (red_out)
    {
        printf("red_out while loop\n");
        // int out_fd;
        // if (red_out->type == APPEND) {
        //     printf("append: %s\n", red_out->file);
        //     out_fd = open(red_out->file, O_RDWR | O_CREAT | O_APPEND, 0644);
        // }
        // else 
        // {
        //     printf("trunc: %s\n", red_out->file);
        //     out_fd = open(red_out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        // }
        // if (out_fd == -1) {
        //     perror("Error opening output file");
        //     exit(EXIT_FAILURE);
        // }
        // dup2(out_fd, STDOUT_FILENO); // Redirect stdout
        // close(out_fd);
        red_out = red_out->next;
    }
}