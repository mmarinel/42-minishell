/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:57 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/07 09:35:31 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

# include "expander.h"

size_t	skip_consecutive_chars(char *string, size_t offset,
			char to_skip, int direction);
size_t	skip_past_last_char(char *str, size_t offset,
			char to_skip, int direction);
// size_t	skip_past_last_single_quote(char *string, size_t offset);


t_bool	dollar_case(char *string, size_t *offset_ref,
			size_t *start_ref, size_t *end_ref);
t_bool	dollar_case(char *string, size_t *offset_ref,
			size_t *start_ref, size_t *end_ref);

#endif