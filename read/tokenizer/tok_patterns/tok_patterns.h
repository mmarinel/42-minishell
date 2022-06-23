/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:39:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 09:10:24 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_H
# define TOK_PATTERNS_H

# include "../tokenizer.h"
# include "tok_patterns_utils/tok_patterns_utils.h"

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list);
size_t	scan_inout_file(char *str, size_t offset, t_token **token_list);
/**
 * @brief ASF to recognize &&, ||, | only
 * 
 * @param str 
 * @return size_t 
 */
size_t	scan_operator(char *str, size_t offset, t_token **token_list);
size_t	scan_cmd_name(char *str, size_t offset, t_token **token_list);
size_t	scan_cmd_arg(char *str, size_t offset, t_token **token_list);
size_t	scan_parenthesis(char *str, size_t offset, t_token **token_list);

#endif