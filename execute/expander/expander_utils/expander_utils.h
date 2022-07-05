/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:57 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 20:34:50 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

# include "expander.h"

size_t	skip_consecutive_quotes(char *string, size_t offset, char quote,
			t_bool *flag);
size_t	skip_past_last_quote(char *str, size_t offset,
			char quote, int increment);
// size_t	skip_past_last_single_quote(char *string, size_t offset);

#endif