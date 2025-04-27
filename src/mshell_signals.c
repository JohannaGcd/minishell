/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_signals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 10:25:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 13:59:43 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

// Signal handler for SIGINT
void sigint_handler(int sig) {
    if (sig == SIGINT) {
        write(STDOUT_FILENO, "\nminishell> ", 12);
    }
}

// Signal handler for SIGQUIT
void sigquit_handler(int sig) {
    if (sig == SIGQUIT) {
        // Ignore SIGQUIT
    }
}

void handle_signal(int mode) {
    if (mode == MAIN_SIG) {
        // Ignore SIGQUIT (Ctrl+\)
        signal(SIGQUIT, sigquit_handler);

        // Handle SIGINT (Ctrl+C) to print prompt on new line
        signal(SIGINT, sigint_handler);
    }
}