/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:04:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 15:00:49 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_UTILS_H
# define TOK_UTILS_H

# include <unistd.h>
# include "../tok_types.h"
# include "../../types.h"

// * user defined functions


size_t	scan_simple_command(char *command_line, size_t offset,
			t_token **token_list);
size_t	scan_prologue(char *command_line, size_t offset,
			t_token **token_list);
size_t	scan_body(char *command_line, size_t offset,
			t_token **token_list);
size_t	scan_epilogue(char *command_line, size_t offset,
			t_token **token_list);
/**
 * @brief this function adds the given token
 * to the end of the current list of tokens
 * 
 * @param tokens the address of the first element
 * in the list (optional if the list is not empty)
 * @param token the next token to store
 */
void	tok_add_back(t_token **token_list, t_token *token);
void	free_tok_list(t_token **token_list);
int		scan_alternate_invariant_spaces_quotes(char *str);

#endif
