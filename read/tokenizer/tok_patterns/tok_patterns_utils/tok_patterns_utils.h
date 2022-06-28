/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:52:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 15:00:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_UTILS_H
# define TOK_PATTERNS_UTILS_H

# include <unistd.h>
# include "../../tok_types.h"
# include "../../../types.h"

// * env vars patterns //
size_t				scan_var(char *str, size_t offset,
						t_token_id tok_type, t_bindings **next_var);
size_t				scan_var_name(char *str, size_t offset, char **name);
size_t				scan_var_value(char *str, size_t offset, char **value,
						t_bool *concat_mode);
size_t				scan_var_mode(char *command_line, size_t offset,
						t_bool *concat_mode);

size_t				scan_initial_keyword_set_token(char *str, size_t offset,
						t_token **token);
size_t				scan_env_revert(t_token *token, size_t offset);
void				add_new_binding(t_token **token_ref,
						t_bindings *next_binding);
void				env_decl_add_token(t_token *scanned_token,
						t_token **token_list);

// * scan loops
size_t				scan_parenthesis(char *command_line, size_t offset,
						t_token **token_list);
size_t				scan_redirs(char *command_line, size_t offset,
						t_token **token_list);

size_t				scan_next_cmd_arg(char *command_line, size_t offset,
						char **cur_arg_string, t_token **token_list);
						
// * to put inside tok_scan_loops
size_t				scan_spaces(char *str, size_t offset);
size_t				scan_invariant_quotes(char *str, size_t offset);
size_t				scan_invariants(char *str, size_t offset);

#endif