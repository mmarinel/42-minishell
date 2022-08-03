/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:36:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 18:06:24 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static size_t	scan_epilogue(char *command_line, size_t offset,
					t_token **token_list);
static size_t	scan_body(char *command_line, size_t offset,
					t_token **token_list);
static size_t	scan_prologue(char *command_line, size_t offset,
					t_token **token_list);

//* end of static declarations //


void	scan(char *command_line, t_token **tok_list_ref)
{
	size_t	offset;
	char	*cursor;

	if (command_line == NULL)
		*tok_list_ref = NULL;
	else
	{
		offset = 0;
		cursor = command_line;
		while (command_line[offset])
		{
			offset = scan_prologue(command_line, offset, tok_list_ref);
			offset = scan_body(command_line, offset, tok_list_ref);
			offset = scan_epilogue(command_line, offset, tok_list_ref);
			if (cursor == command_line + offset)
				break ;
			cursor = command_line + offset;
		}
		if (offset < ft_strlen(command_line))
		{
			put_error(TOK_NOT_RECOGNIZED_ERROR, 258, command_line + offset);
			free_tok_list(tok_list_ref);
		}
	}
}

static size_t	scan_prologue(char *command_line, size_t offset,
					t_token **token_list)
{
	size_t	pre_offset;

	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_redirs(command_line, offset, token_list);
	return (offset);
}

static size_t	scan_body(char *command_line, size_t offset,
					t_token **token_list)
{
	// printf(YELLOW "inside scan_body\n" RESET);
	offset = scan_invariants(command_line, offset);
	// if (ft_strncmp(command_line + offset, "export", 6) == 0
	// 	|| ft_strncmp(command_line + offset, "unset", 5) == 0)
	if (e_true == is_env_statement(command_line, offset))
		return (scan_env_declaration(command_line, offset, token_list));
	else
		return (scan_simple_command(command_line, offset, token_list));
}

static size_t	scan_epilogue(char *command_line, size_t offset,
					t_token **token_list)
{
	size_t	pre_offset;

	offset = scan_redirs(command_line, offset, token_list);
	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_operator(command_line, offset, token_list);
	return (offset);
}
