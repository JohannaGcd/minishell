/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/26 08:44:32 by sveta         #+#    #+#                 */
/*   Updated: 2025/04/26 08:48:04 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/executer.h"

int	main(int argc, char **argv, char **envp)
{
	t_msh_state		msh_state;
	t_minishell		mshell;
	t_msh_function	fun[MSH_EXIT];

	(void)argv;
	(void)argc;
	fun[MSH_READLINE] = fn_msh_readline;
	fun[MSH_LEXER] = fn_msh_lexer;
	fun[MSH_SYNTAXER] = fn_msh_syntaxer;
	fun[MSH_PARSER] = fn_msh_parser;
	fun[MSH_EXECUTER] = fn_msh_executer;
	fun[MSH_CLEAN] = fn_msh_clean;
	msh_state = fn_msh_start(&mshell, envp);
	while (msh_state != MSH_EXIT)
	{
		msh_state = fun[msh_state](&mshell);
	}
	return (0);
}
