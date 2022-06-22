/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:39:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 12:51:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_H
# define TOK_PATTERNS_H

# include "../tokenizer.h"
# include "tok_patterns_utils/tok_patterns_utils.h"

int	scan_var(char *str, t_token **token_list);
int	scan_export_keyword(char *cursor);
int	scan_inout_file(char *str, t_token **token_list);
/**
 * @brief ASF to recognize &&, ||, | only
 * 
 * @param str 
 * @return int 
 */
int	scan_operator(char *str, t_token **token_list);
int	scan_cmd_name(char *str, t_token **token_list);
int	scan_cmd_arg(char *str, t_token **token_list);
int	scan_parenthesis(char *str, t_token **token_list);

#endif