/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 22:10:48 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/27 17:26:24 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	handle_arg_with_equal(char *argsi, char **var, char **value)
{
	if (equal_in_mid(argsi))
	{
		*var = ft_substr(argsi, 0, ft_strchr(argsi, '=') - argsi);
		*value = ft_substr(argsi, (ft_strchr(argsi, '=')
					- argsi) + 1, ft_strlen(argsi));
	}
	else if (equal_is_last(argsi))
	{
		*var = ft_substr(argsi, 0, ft_strchr(argsi, '=')
				- argsi);
		*value = ft_strdup("");
	}
}

void	free_var_value(char *var, char *value)
{
	free(var);
	free(value);
}

void	handle_export_argument(char **args, t_minishell *mshell, int *i)
{
	char		*var;
	char		*value;

	if (args[*i][0] == '=')
	{
		not_valid(args[*i], mshell);
		return ;
	}
	if (ft_strrchr(args[*i], '='))
		handle_arg_with_equal(args[*i], &var, &value);
	else if (ft_is_number(args[*i]) || ft_strrchr(args[*i], '-'))
	{
		not_valid(args[*i], mshell);
		return ;
	}
	else
		return ;
	if (ft_strrchr(var, '-'))
	{
		not_valid(var, mshell);
		free_var_value(var, value);
		return ;
	}
	set_or_update_env(mshell, var, value);
	free_var_value(var, value);
}

void	exec_export(char **args, t_minishell *mshell)
{
	int			count;
	int			i;

	i = 1;
	mshell->envs->status = 0;
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
