/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:52:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 09:25:47 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_UTILS_H
# define TOK_PATTERNS_UTILS_H

# include "../tok_patterns.h"
# include "../../tok_types.h"


int					scan_export_keyword(char *str, size_t offset);
size_t				scan_var_name(char *cursor, char **name);
size_t				scan_var_value(char *cursor, char **value);
size_t				scan_var(char *str, size_t offset,
						t_var_ass_content **next_var);
int					scan_spaces(char *str);
int					scan_invariant_quotes(char *str);

#endif