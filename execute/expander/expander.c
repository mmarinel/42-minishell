/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 17:15:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expander(char *args)
{
	size_t	expansion_start;
	size_t	expansion_end;

	while (e_true == is_expandable(args, &expansion_start, &expansion_end))
	{
		args = expand(args, expansion_start, expansion_end);
	}
	return (args);
}

t_bool	is_expandable(char *string, size_t *start_ref, size_t *end_ref)
{
	size_t	i;
	t_bool	in_double_quotes;

	if (!string)
		return (e_false);
	in_double_quotes = e_false;
	i = 0;
	while (string[i])
	{
		if (string[i] == '"')
			i = skip_consecutive_double_quotes(string, i, &in_double_quotes);
		else if (e_false == in_double_quotes && string[i] == '\'')
			i = skip_to_last_single_quote(string, i);
		{
			if (((string[i] == '*' && e_false == in_double_quotes)
					|| string[i] == '$')
				&& (e_true == ft_is_alpha(string[i + 1]
					|| '_' == string[i + 1])))
			{
				expansion_segment_set_boundaries(start_ref, end_ref);
				return (e_true);
			}
		}
		i++;
	}
	return (e_false);
}
