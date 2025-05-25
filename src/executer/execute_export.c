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

static void	handle_equal_at_end(char *arg, char **var, char **value)
{
	*var = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	*value = ft_strdup("");
}

static int	is_invalid_argument(char *arg)
{
	return (arg[0] == '=' || ft_strrchr(arg, '-') || ft_is_number(arg));
}

static int	is_invalid_var(char *var)
{
	if (ft_strrchr(var, '-'))
		return (1);
	if (ft_is_number(var))
		return (1);
	if (ft_strchr(var, '='))
		return (1);
	if (ft_strchr(var, ' '))
		return (1);
	if (ft_strchr(var, '\t'))
		return (1);
	return (0);
}

void	handle_export_argument(char **args, t_minishell *mshell, int *i)
{
	char	*var;
	char	*value;

	if (is_invalid_argument(args[*i]))
	{
		not_valid(args[*i], mshell);
		return ;
	}
	if (equal_in_mid(args[*i]))
		handle_equal_in_mid(args[*i], &var, &value);
	else if (equal_is_last(args[*i]))
		handle_equal_at_end(args[*i], &var, &value);
	else
		return ;
	if (is_invalid_var(var))
	{
		not_valid(var, mshell);
		free(var);
		free(value);
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
