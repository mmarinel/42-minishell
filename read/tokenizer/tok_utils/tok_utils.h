/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:04:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/14 10:30:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_UTILS_H
# define TOK_UTILS_H

# include <unistd.h>
# include "../tok_patterns/tok_patterns.h"
# include "../../../colors.h"
# include "../../../utils/ft_utils.h"
# include "../tok_types.h"
# include "../../../types.h"
# include "../../../global.h"
# include "../../../env/env_utils/env_utils.h"
// * user defined functions

size_t	scan_simple_command(char *command_line, size_t offset,
			t_token **token_list);
void	tok_add_back(t_token **token_list, t_token *token);
void	free_tok_list(t_token **token_list);

size_t	occ_outside_quotes(char *str, char to_count);
int		scan_alternate_invariant_spaces_quotes(char *str);
size_t	bash_next_word_len(char *command_line, size_t offset);

size_t	scan_spaces(char *str, size_t offset);
size_t	scan_invariant_quotes(char *str, size_t offset);
size_t	scan_invariants(char *str, size_t offset);

char	*tok_to_string(t_token *token);
void	print_token(t_token *token);

t_bool	is_env_statement(char *command_line, size_t offset);

#endif