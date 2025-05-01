/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_signals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 10:25:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/01 10:34:37 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

void	sig_ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    set_main_signal()
{
    struct sigaction	sa;

    sa.sa_handler = sig_ctrl_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
    // exit from minishell ?? 
	exit(1);
}

void set_heredoc_signal()
{
    struct sigaction	sa;

    sa.sa_handler = sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

//SIG_DFL: This constant sets the signal handler to the default action defined by the system. 
//For both SIGINT and SIGQUIT, this usually means terminating the process.
//SIG_IGN: This constant sets the signal handler to ignore the signal, 
//meaning the process will not respond to the signal.

void handle_signal(int mode) {
    if (mode == MAIN_SIG)
    {
        set_main_signal();
    }
    else if (mode == HEREDOC)
    {
        set_heredoc_signal();
    }
    else if (mode == CHILD_SIG)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else 
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}

}