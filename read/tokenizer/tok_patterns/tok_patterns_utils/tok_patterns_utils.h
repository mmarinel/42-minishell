/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:52:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 14:52:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_UTILS_H
# define TOK_PATTERNS_UTILS_H

# include "../tok_patterns.h"
# include "../../tok_types.h"

size_t				scan_var_name(char *cursor, char **name);
size_t				scan_var_value(char *cursor, char **value);
t_var_ass_content	*scan_var_set_cursor(char *cursor, char **cursor_ref, int assignment_cardinal);
int					scan_spaces(char *str);
int					scan_invariant_quotes(char *str);

#endif