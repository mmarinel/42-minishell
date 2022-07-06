/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/06 15:14:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

size_t	skip_consecutive_chars(char *string, size_t offset, char quote)
{
	while (string[offset] == quote)
		offset++;
	return (offset);
}

// size_t	skip_past_last_single_quote(char *string, size_t offset)
// {
// 	while (string[offset])
// 	{
// 		if (string[offset] == '\'')
// 			return (offset + 1);
// 	}
// 	return (offset);
// }

size_t	skip_past_last_char(char *str, size_t offset,
			char quote, int increment)
{
	int	i;

	i = offset;
	while (e_true)
	{
		if (i == 0 || str[i] == '\0')
			return (i);
		if (str[i] == quote)
			return (i + increment);
		i += increment;
	}
	return ((size_t)-1);
}
