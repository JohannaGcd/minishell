/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/08 15:22:07 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/12 12:49:56 by jguacide      ########   odam.nl         */
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
typedef void (*t_token_func)(int *, char *, char);


// lexer_list_utils.c
t_token		*token_list_find_last(t_token *token_list_node);
void		token_list_add_back(t_token **token_list_head, t_token *new_token);
t_token		*create_new_token(void);
t_token		*create_token(int type, char *str);

// lexer_utils.c
void		pipe_token(int *current_pos, char *input_str, char c);
void		space_token(int *current_pos, char *input_str, char c);
void		quote_token(int *current_pos, char *input_str, char c);
void		redirect_token(int *current_pos, char *input_str, char c);
void		word_token(int *current_pos, char *input_str, char c);
void		env_token(int *current_pos, char *input_str, char c);
int			ft_isspace(char c);
void		clean_tokens(t_token *tokens);

// Syntax Checker
// -> Checks whether the tokens respect grammar rules for BASH

// syntaxer.c
int			syntaxer(t_token *token_list);
int			check_token_syntax(t_token *prev_token, t_token *curr_token);
t_token		*skip_space_token(t_token *current_token);

// syntaxer_utils.c
int			pipe_syntaxer(t_token *prev_token, t_token *curr_token);
int			quote_syntaxer(t_token *prev_token, t_token *curr_token);
int			word_syntaxer(t_token *prev_token, t_token *curr_token);
int			redir_syntaxer(t_token *prev_token, t_token *curr_token);
int			na_syntaxer(t_token *prev_token, t_token *curr_token);
int			env_syntaxer(t_token *prev_token, t_token *curr_token);

// Parsing
// -> Processes the tokens according to a grammar and builds the command structs

// parser.c
t_command	*extract_commands(t_token *token_list);
t_command	*init_command(void);
void		fill_command(t_command **new_command, t_token *token_list);
void		get_command_args(t_command **new_command, t_token *token_list);
void		handle_redirections(t_command *command, t_token *tokens);
int			count_command_args(t_token *token_list);
void		fill_redirections(t_command **command, t_token *tokens);
void		copy_command_args(char **command_args, t_token *token_list);

// parser_utils.c

t_token		*skip_to_pipe(t_token *token);
t_command	*command_list_find_last(t_command *command_list_head);
void		command_list_add_back(t_command **command_list_head,
				t_command *new_command);
t_command	*init_command(void);

#endif