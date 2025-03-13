#include "../include/minishell.h"
#include "../include/executer.h"

int	main(int argc, char **argv, char **envp)
{
	t_msh_state	msh_state;
	t_minishell mshell;
	t_msh_function		fun[MSH_EXIT];
	(void)argv; // to avoid the error of unused variable with WWE flags
	(void)argc;   // to avoid the error of unused variable with WWE flags
	
	
	fun[MSH_READLINE] = fn_msh_redline;
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
	//int i;
	////const char prompt[] = "minishell > ";
	//t_token *test;
	//t_token *tmp;

	// prompt = "minishell > ";
	
	// t_env_node *tmp_node;
	// printf("env inited\n");
	// tmp_node = envs->env;
	// while (tmp_node)
	// {
	// 	printf("var=%s\n", tmp_node->var);
	// 	printf("value=%s\n", tmp_node->value);
	// 	tmp_node = tmp_node->next;
	// }
	//while (1)
	// {
	// 	input_str = readline(prompt);
	// 	test = extract_tokens(input_str);

	// 	tmp = test;
	// 	i = 0;
	// 	while (tmp != NULL)
	// 	{
	// 		printf("token %d:<%s>, type=%u\n", i, tmp->str, tmp->type);
	// 		i++;
	// 		tmp = tmp->next;
	// 	}
	// 	// if (syntaxer(test) != 0)
	// 	// {
	// 	// 	printf("there is a syntax error");
	// 	// 	return (1);
	// 	// };
	// 	printf("expand\n");
	// 	expand_env(test, envs);
	// 	tmp = test;
	// 	i = 0;
	// 	while (tmp != NULL)
	// 	{
	// 		printf("token %d:<%s>, type=%u\n", i, tmp->str, tmp->type);
	// 		i++;
	// 		tmp = tmp->next;
	// 	}
	// 	extract_commands(test);
	// }
	/*t_command command1 = 
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
	*/
