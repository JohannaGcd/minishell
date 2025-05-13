/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 13:38:42 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/13 16:12:40 by spanfilo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Allocates and sets redirection type.
void	set_redirection(t_redirection **redir, t_token *tokens, int is_in)
{
	*redir = ft_calloc(1, sizeof(t_redirection));
	if (!*redir)
	{
		perror("calloc set_redirections failed");
		//exit(EXIT_FAILURE);
	}
	if (is_in)
	{
		if (ft_strncmp(tokens->str, "<<", 2) == 0)
			(*redir)->type = HEREDOC;
		else
			(*redir)->type = RED_IN;
	}
	else
	{
		if (ft_strncmp(tokens->str, ">>", 2) == 0)
			(*redir)->type = APPEND;
		else
			(*redir)->type = RED_OUT;
	}
	tokens = skip_spaces(tokens->next);
	(*redir)->file = ft_strdup(tokens->str);
}

// Fills the redirections for the current command
void	fill_redirections(t_command **command, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type != M_SPACE)
		{
			if (tokens->type == REDIRECT_IN || tokens->type == HEREDOC)
				set_redirection(&(*command)->in, tokens, 1);
			else if (tokens->type == REDIRECT_OUT || tokens->type == APPEND)
				set_redirection(&(*command)->out, tokens, 0);
		}
		tokens = tokens->next;
	}
}
