/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/15 19:06:12 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	handle_export_argument(char **args, t_minishell *mshell, int *i)
{
	char		*var;
	char		*value;

	if (args[*i][0] == '=')
	{
		not_valid(args[*i], mshell);
		return ;
	}
	else if (equal_in_mid(args[*i]))
	{
		var = ft_substr(args[*i], 0, ft_strchr(args[*i], '=') - args[*i]);
		value = ft_substr(args[*i], (ft_strchr(args[*i], '=')
					- args[*i]) + 1, ft_strlen(args[*i]));
	}
	else if (equal_is_last(args[*i]))
	{
		var = ft_substr(args[*i], 0, ft_strchr(args[*i], '=')
				- args[*i]);
		value = ft_substr(args[*i + 1], 0, ft_strlen(args[*i + 1]));
	}
	else if (ft_strrchr(args[*i], '-') || ft_is_number(args[*i]))
	{
		not_valid(args[*i], mshell);
		return ;
	}
	else
		return ;
	if (ft_strrchr(var, '-'))
	{
		not_valid(var, mshell);
		return ;
	}
	set_or_update_env(mshell, var, value);
	free(var);
	free(value);
}

void	exec_export(char **args, t_minishell *mshell)
{
	int			count;
	int			i;

	i = 1;
	count = number_arguments(args);
	if (count == 1)
		exec_export_print(mshell);
	else
	{
		while (i < count)
		{
			handle_export_argument(args, mshell, &i);
			i++;
		}
	}
}
