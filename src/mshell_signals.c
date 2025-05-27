/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshell_signals.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 10:25:54 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/27 18:31:15 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	sig_ctrl_c(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_main_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_ctrl_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc(int signum)
{
	g_signal_received = signum;
	rl_done = 1;
}

void	set_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal(int mode)
{
	if (mode == MAIN_SIG)
	{
		set_main_signal();
		rl_event_hook = NULL;
	}
	else if (mode == HEREDOC_SIG)
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
