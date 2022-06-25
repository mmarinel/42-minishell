/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:52:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/25 09:01:27 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_UTILS_H
# define TOK_PATTERNS_UTILS_H

# include "../tok_patterns.h"
# include "../../tok_types.h"

size_t				scan_var_name(char *str, size_t offset, char **name);
size_t				scan_var_value(char *str, size_t offset, char **value,
						t_bool *concat_mode);
size_t				scan_var_mode(char *command_line, size_t offset,
						t_bool *concat_mode);
size_t				scan_var(char *str, size_t offset,
						t_token_id tok_type, t_var_ass_content **next_var);
size_t				scan_next_cmd_arg(char *command_line, size_t offset,
						char **cur_arg_string, t_token **token_list);
size_t				scan_spaces(char *str, size_t offset);
size_t				scan_invariant_quotes(char *str, size_t offset);
size_t				scan_invariants(char *str, size_t offset);

#endif