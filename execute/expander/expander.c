/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/06 12:35:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expander(char *args)
{
	size_t	expansion_start;
	size_t	expansion_end;
	size_t	cur_offset;

	cur_offset = 0;
	while (e_true == is_expandable(args + cur_offset,
			&expansion_start,
			&expansion_end)
	)
	{
		args = expand(args, expansion_start, expansion_end);
		cur_offset = expansion_end + 1;
		if (args[cur_offset] == '\0')
			break ;
	}
	return (args);
}

// star_case(string, &i, start_ref, end_ref)

static size_t	expander_quotes_handling(char *string, size_t offset,
					t_bool *in_double_quotes_ref)
{
	if (string[offset] == '"')
	{
		offset = skip_consecutive_quotes(string, offset, '"');
		flip(in_double_quotes_ref);
	}
	else if (string[offset] == '\'' && e_false == *in_double_quotes_ref)
	{
		offset = skip_consecutive_quotes(string, offset, '\'');
		offset = skip_past_last_quote(string, offset, '\'', +1);
	}
	return (offset);
}


t_bool	star_case(char *string, size_t *offset_ref,
			size_t *start_ref, size_t *end_ref)
{
	*offset_ref = skip_consecutive_quotes(string, *offset_ref, '*');
	if (string[*offset_ref] == '/')
	{
		*offset_ref = skip_consecutive_quotes(string, *offset_ref + 1, '*');
		return (e_false);
	}
	else
	{
		*offset_ref -= 1;
		star_expansion_segment_set_boundaries(string, *offset_ref, start_ref, end_ref);
		return (e_true);
	}
}

t_bool	dollar_case(char *string, size_t *offset_ref,
			size_t *start_ref, size_t *end_ref)
{
	*start_ref = *offset_ref;
	*offset_ref += 1;
	while (e_true)
	{
		if (string[*offset_ref] == '$'
			|| string[*offset_ref] == '*')
		{
			*end_ref = *offset_ref;
			return (e_true);
		}
		if (string[*offset_ref] == '\0'
			|| e_false == bash_control_character(string[*offset_ref]))
			break ;
		*offset_ref += 1;
	}
	*end_ref = *offset_ref - 1;
	return (e_true);
}

t_bool	is_expandable(char *string,
			size_t *start_ref,
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
		i = expander_quotes_handling(string, i, &in_double_quotes);
		if (string[i] == '*' || string[i] == '$')
		{
			if (string[i] == '*' && e_false == in_double_quotes)
				if (star_case(string, &i, start_ref, end_ref))
					return (e_true);
			if (string[i] == '$')
				if (dollar_case(string, &i, start_ref, end_ref))
					return (e_true);
		}
		else
			i++;
	}
	return (e_false);
}

void	star_expansion_segment_set_boundaries(char *string, size_t special_char_pos,
			size_t *start_ref, size_t *end_ref)
{
	*start_ref = star_expansion_segment_set_part(string, special_char_pos, -1);
	*end_ref = star_expansion_segment_set_part(string, special_char_pos, +1);
}

size_t	star_expansion_segment_set_part(char *string, size_t special_char_pos,
		int increment)
{
	int	point;

	if (special_char_pos + increment < 0
		|| string[special_char_pos + increment] == '\0')
		return (special_char_pos);
	point = special_char_pos + increment;
	while (e_true)
	{
		if (string[point] == '"' || string[point] == '\'')
		{
			point = skip_past_last_quote(string, point + increment,
						string[point], increment);
		}
		if (e_true == bash_control_character(string[point])) // || string[point] == '*')
			return (point - increment);
		if (point == 0 || string[point + increment] == '\0')
			return (point);
		point += increment;
	}
	return (-1);
}
