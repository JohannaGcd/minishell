/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:44:32 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/06 18:31:19 by sveta         ########   odam.nl         */
/*   Updated: 2025/05/06 14:26:53 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

int	main(int argc, char **argv, char **envp)
{
	t_msh_state		msh_state;
	t_minishell		mshell;
	t_msh_function	fun[MSH_EXIT];
	int				exit_status;

	exit_status=0;
	(void)exit_status;
	(void)argv;
	(void)argc;
	fun[MSH_READLINE] = mshell_readline;
	fun[MSH_LEXER] = mshell_lexer;
	fun[MSH_SYNTAXER] = mshell_syntaxer;
	fun[MSH_PARSER] = mshell_parser;
	fun[MSH_EXECUTER] = mshell_executer;
	fun[MSH_CLEAN] = mshell_clean;
	msh_state = mshell_start(&mshell, envp);
	while (msh_state != MSH_EXIT)
	{
		handle_signal(MAIN_SIG);
		msh_state = fun[msh_state](&mshell); //, &exit_status
	}
	return (0); // TODO: exit with Exit status
}
