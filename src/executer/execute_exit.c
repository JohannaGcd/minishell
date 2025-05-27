/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/19 21:32:27 by sveta         #+#    #+#                 */
/*   Updated: 2025/05/27 18:06:15 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	is_valid_long(char *str)
{
	long int	num;
	char		*str_new;

	num = ft_atoi_long(str);
	str_new = ft_long_itoa(num);
	if (str[0] == '+')
	{
		if (ft_strncmp(str + 1, str_new, ft_strlen(str)))
		{
			free(str_new);
			return (0);
		}
	}
	else
	{
		if (ft_strncmp(str, str_new, ft_strlen(str)))
		{
			free(str_new);
			return (0);
		}
	}
	free(str_new);
	return (1);
}

int	is_valid_exit_number(char *str)
{
	int			i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (is_valid_long(str) == 0)
		return (0);
	return (1);
}

int	exec_exit(char **command_args, t_minishell *mshell, int *exit_status)
{
	*exit_status = mshell->envs->status;
	ft_putendl_fd("exit", 1);
	if (command_args[1] && command_args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		*exit_status = 1;
		mshell->is_exit = 0;
		mshell->envs->status = 1;
		return (1);
	}
	if (command_args[1])
	{
		if (!is_valid_exit_number(command_args[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(command_args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			mshell->envs->status = 255;
			*exit_status = 2;
		}
		else
			*exit_status = ft_atoi(command_args[1]) % 256;
	}
	mshell->is_exit = 1;
	return (*exit_status);
}
