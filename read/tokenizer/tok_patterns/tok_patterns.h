/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:39:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 12:11:18 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_PATTERNS_H
# define TOK_PATTERNS_H

// # include "../tokenizer.h"
// # include "tok_patterns_utils/tok_patterns_utils.h"

// * standard libraries //
# include <unistd.h>

// * types //
# include "../tok_types.h"
# include "../../../types.h"

// * user defined helper functions //
# include "tok_patterns_granular/tok_patterns_granular.h"
# include "../tok_utils/tok_utils.h"
# include "../../../utils/ft_utils.h"

// * start of declarations //

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list);
size_t	scan_inout_file(char *str, size_t offset, t_token **token_list);
size_t	scan_operator(char *str, size_t offset, t_token **token_list);
size_t	scan_single_par(char *command_line, size_t offset,
			t_token **token_list);
size_t	scan_cmd_name(char *str, size_t offset, t_token **token_list);
size_t	scan_cmd_arg(char *str, size_t offset, t_token **token_list);
size_t	scan_parenthesis(char *str, size_t offset, t_token **token_list);

#endif