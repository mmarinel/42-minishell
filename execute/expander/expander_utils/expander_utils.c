/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/07 09:35:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

size_t	skip_consecutive_chars(char *string, size_t offset,
			char to_skip, int direction)
{
	while (string[offset] == to_skip)
		offset += direction;
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
			char to_skip, int direction)
{
	int	i;

	i = offset;
	while (e_true)
	{
		if (i == 0 || str[i] == '\0')
			return (i);
		if (str[i] == to_skip)
			return (i + direction);
		i += direction;
	}
	return ((size_t)-1);
}
