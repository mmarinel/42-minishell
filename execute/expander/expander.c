/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 20:32:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expander(char *args)
{
	size_t	expansion_start;
	size_t	expansion_end;
	size_t	special_char_pos;

	while (e_true == is_expandable(args,
			&expansion_start,
			&special_char_pos,
			&expansion_end)
	)
	{
		args = expand(args, expansion_start, special_char_pos, expansion_end);
	}
	return (args);
}

t_bool	is_expandable(char *string,
			size_t *start_ref,
			size_t *special_char_pos_ref,
			size_t *end_ref)
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
		{
			i = skip_consecutive_quotes(string, i, '"', &in_double_quotes);
		}
		else if (e_false == in_double_quotes && string[i] == '\'')
		{
			i = skip_consecutive_quotes(string, i, '\'', NULL);
			i = skip_past_last_quote(string, i, '\'', +1);//i = skip_past_last_single_quote(string, i);
		}
		{
			if ((string[i] == '*' && e_false == in_double_quotes)
				|| (string[i] == '$'
					&& (e_true == ft_is_alpha(string[i + 1]
						|| '_' == string[i + 1]))))
			{
				*special_char_pos_ref = i;
				expansion_segment_set_boundaries(string, i, start_ref, end_ref);
				return (e_true);
			}
		}
		i++;
	}
	return (e_false);
}

void	expansion_segment_set_boundaries(char *string, size_t special_char_pos,
			size_t *start_ref, size_t *end_ref)
{
	*start_ref = expansion_segment_set_part(string, special_char_pos, -1);
	*end_ref = expansion_segment_set_part(string, special_char_pos, +1);
}

size_t	expansion_segment_set_part(char *string, size_t special_char_pos,
		int increment)
{
	int	point;

	if (special_char_pos == 0 || string[special_char_pos + increment] == '\0')
		return (special_char_pos);
	point = special_char_pos + increment;
	while (e_true)
	{
		if (string[point] == '"' || string[point] == '\'')
		{
			point = skip_past_last_quote(string, point + increment,
						string[point], increment);
		}
		if (e_true == bash_control_character(string[point]))
			return (point - increment);
		if (point == 0 || string[point + increment] == '\0')
			return (point);
		point += increment;
	}
	return (-1);
}
