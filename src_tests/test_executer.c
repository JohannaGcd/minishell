#include "../include/minishell.h"
#include "../include/executer.h"

int test_ex_one_command()
{
    t_command command1 = 
	{
		.command_args = (char *[]){"ls", "-l", "/", NULL},
		.in = NULL,
		.out = NULL,
		.next = NULL
	};
    execute_commands(&command1);
}

int test_ex_two_commands()
{
    t_command command1 = 
	{
		.command_args = (char *[]){"ls", "-l", "/", NULL},
		.in = NULL,
		.out = NULL,
		.next = NULL
	};
	t_command command2 = 
	{
		.command_args = (char *[]){"echo", "Hello, World!", NULL},
		.in = NULL,
		.out = NULL,
		.next = NULL
	};
	command1.next = &command2;

	execute_commands(&command1);
}
