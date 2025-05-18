/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 13:38:42 by jguacide      #+#    #+#                 */
/*   Updated: 2025/05/18 14:20:02 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_red(t_redirection	**new_redir, t_token *tokens, int is_in)
{
	if (is_in)
	{
		if (ft_strncmp(tokens->str, "<<", 2) == 0)
			(*new_redir)->type = HEREDOC;
		else
			(*new_redir)->type = RED_IN;
	}
	else
	{
		if (ft_strncmp(tokens->str, ">>", 2) == 0)
			(*new_redir)->type = APPEND;
		else
			(*new_redir)->type = RED_OUT;
	}
}

// Allocates and sets redirection type.
void	set_redirection(t_redirection **redir, t_token *tokens, int is_in)
{
	t_redirection	*new_redir;
	t_token			*tok_file;
	t_redirection	*current;

	new_redir = ft_calloc(1, sizeof(t_redirection));
	if (!new_redir)
	{
		perror("calloc set_redirections failed");
		exit(EXIT_FAILURE);
	}
	set_red(&new_redir, tokens, is_in);
	tok_file = skip_spaces(tokens->next);
	(new_redir)->file = ft_strdup(tok_file->str);
	(new_redir)->next = NULL;
	new_redir->fd = -1;
	if (*redir == NULL)
		*redir = new_redir;
	else
	{
		current = *redir;
		while (current->next != NULL)
			current = current->next;
		current->next = new_redir;
	}
}

// Fills the redirections for the current command
void	fill_redirections(t_command **command, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type != M_SPACE)
		{
			if (tokens->type == REDIRECT_IN)
				set_redirection(&((*command)->in), tokens, 1);
			else if (tokens->type == REDIRECT_OUT)
				set_redirection(&((*command)->out), tokens, 0);
		}
		tokens = tokens->next;
	}
}
