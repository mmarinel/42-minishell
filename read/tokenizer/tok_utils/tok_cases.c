/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:36:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/12 12:53:30 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

size_t	scan_prologue(char *command_line, size_t offset,
			t_token **token_list)
{
	size_t	pre_offset;

	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_redirs(command_line, offset, token_list);
	return (offset);
}

size_t	scan_body(char *command_line, size_t offset, t_token **token_list)
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

size_t	scan_epilogue(char *command_line, size_t offset,
			t_token **token_list)
{
	size_t	pre_offset;

	offset = scan_redirs(command_line, offset, token_list);
	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_operator(command_line, offset, token_list);
	return (offset);
}
