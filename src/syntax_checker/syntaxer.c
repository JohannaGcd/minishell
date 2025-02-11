#include "minishell.h"

int	check_syntax(t_token *token_list)
{
	if (!token_list)
		return (1);
	void (*check_grammar_rules[])(char *str) = {
		[TOKEN] = NULL,
		[PIPE] = pipe_syntaxer,
	};
	check_grammar_rules[token_list->type](token_list->str);
	return (0);
}

/* SYNTAX RULES:

// 1. PIPE |
	A pipe is always followed by a second command:
		-> Pipe at the bginning or end of the line
		-> Two consecutive || without a command (WORD token) in between
		ex: | ls (pipe cannot start a command).

// 	2. COMMANDS
	A valid command consists of a command name followed by optional arguments
		-> Check the commands follows the proper order [command] [argument] [redirection]

// 2. Unclosed quotes or mismatched quotes ' "
		ex: echo "Hello (missing closing ").

// 3. Redirections < > << >>
	Input/Output Redirections or Heredoc.
		-> Check that there is a file name after < > >>
			No redirection symbols should appear without corresponding commands or arguments
		-> Missing delimiter after <<
		-> A redirective before or after a pipe should be valid
		ex: ls > (missing output file)


// 4. ENVIRONMENT VARIABLES ($)
		-> Ensure WORD token (variable name) after $
		-> Or $?
		Ex: echo $ (no variable name after $)

// 5. SPECIAL CHARACTERS
		-> DO not allow special characters (like ; or \)
*/