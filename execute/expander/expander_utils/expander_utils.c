/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 20:34:47 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

size_t	skip_consecutive_quotes(char *string, size_t offset, char quote,
			t_bool *flag)
{
	if (flag)
		*flag = e_true;
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

size_t	skip_past_last_quote(char *str, size_t offset,
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
