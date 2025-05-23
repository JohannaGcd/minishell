/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:07 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/22 18:49:04 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// lexer.c
t_token		*extract_tokens(char *input_str);
void		fill_token_info(int *current_pos, char *input_str,
				t_token *new_token);
int			get_token_hint(char c);
typedef void	(*t_token_func)(int *current_pos, char *input_str, char c);

// lexer_list_utils.c
t_token		*token_list_find_last(t_token *token_list_node);
void		token_list_add_back(t_token **token_list_head, t_token *new_token);
t_token		*create_new_token(void);
t_token		*create_token(int type, char *str);

// lexer_utils.c
void		pipe_token(int *current_pos, char *input_str, char c);
void		quote_token(int *current_pos, char *input_str, char c);
void		redirect_token(int *current_pos, char *input_str, char c);
void		word_token(int *current_pos, char *input_str, char c);
void		space_token(int *current_pos, char *input_str, char c);
int			ft_isspace(char c);

// lexer_token_env.c
void		env_token(int *current_pos, char *input_str, char c);

// lexer_clean.c
void		clean_tokens(t_token *tokens);

// syntaxer.c
int			syntaxer(t_token *token_list);
int			check_token_syntax(t_token *prev_token, t_token *curr_token);
t_token		*skip_space_token(t_token *current_token);
typedef int		(*t_syntax_func)(t_token *prev_token, t_token *curr_token);
int			na_syntaxer(t_token *prev_token, t_token *curr_token);

// syntaxer_utils.c
int			pipe_syntaxer(t_token *prev_token, t_token *curr_token);
int			quote_syntaxer(t_token *prev_token, t_token *curr_token);
int			word_syntaxer(t_token *prev_token, t_token *curr_token);
int			redir_syntaxer(t_token *prev_token, t_token *curr_token);
int			env_syntaxer(t_token *prev_token, t_token *curr_token);

// parser_cmd_arg.c
char		*handle_quoted_arg(t_token *token);
int			count_command_args(t_token *token_list);
void		copy_command_args(char **command_args, t_token *token_list);
void		fill_command(t_command **new_command, t_token *token_list);
t_command	*extract_commands(t_token *token_list);

// parser_redir.c
void		set_redirection(t_redirection **redir, t_token *tokens, int is_in);
void		fill_redirections(t_command **command, t_token *tokens);
void		handle_token_counter(t_token **token, int *counter, int *redir);

// parser_utils.c
t_token		*skip_spaces(t_token *token);
t_token		*skip_to_pipe(t_token *token);
t_command	*command_list_find_last(t_command *command_list_head);
void		command_list_add_back(t_command **command_list_head,
				t_command *new_command);
t_command	*init_command(void);
char		*handle_quoted_arg(t_token *token);
int			count_command_args(t_token *token_list);
void		skip_initial_tokens(t_token **token_list);
int			count_len(int len, t_token **token_list);
int			correct_token(t_token **token_list);

// parser_cmd_arg_utils.c
void		perror_allocate_with_exit(void);
char		*build_argument_string(t_token **token_list);
void		skip_redirection_tokens(t_token **token_list);
void		process_argument(t_token **token_list, char **command_args, int *i);

#endif