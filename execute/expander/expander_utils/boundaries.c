/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundaries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:10:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/07 11:16:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

static size_t	star_expansion_segment_set_part(char *string, size_t special_char_pos,
		int increment);
static void	star_expansion_segment_set_boundaries(char *string, size_t special_char_pos,
			size_t *start_ref, size_t *end_ref);

// * end of static declarations //


size_t	star_case_set_beginning(char *string, size_t *offset_ref)
{
	size_t	offset;
	// char	quote;

	offset = *offset_ref;
	while (e_true)
	{
		while (string[offset] == '\''
				|| string[offset] == '"')
		{
			offset = skip_past_last_char(string, offset - 1, string[offset], -1);
			// quote = string[offset];
			// offset = skip_consecutive_chars(string, offset, quote, -1);
			// offset = skip_past_last_char(string, offset, quote, -1);
			// offset = skip_consecutive_chars(string, offset, quote, -1);
		}
		if (e_true == bash_control_character(string[offset]))
			return (offset + 1);
		else if (offset == 0)
			return (offset);
		offset--;
	}
	return ((size_t)-1);
}

size_t	star_case_set_end(char *string, size_t *offset_ref)
{
	size_t	offset;
	// char	quote;

	offset = *offset_ref;
	while (e_true)
	{
		while (string[offset] == '\''
				|| string[offset] == '"')
		{
			offset = skip_past_last_char(string, offset + 1, string[offset], +1);
			// quote = string[offset];
			// offset = skip_consecutive_chars(string, offset, quote, -1);
			// offset = skip_past_last_char(string, offset, quote, -1);
			// offset = skip_consecutive_chars(string, offset, quote, -1);
		}
		if (e_true == bash_control_character(string[offset]))
			return (offset - 1);
		else if (string[offset] == '\0')
			return (offset);
		offset++;
	}
	return ((size_t)-1);
}

// t_bool	star_case(char *string, size_t *offset_ref,
// 			size_t *start_ref, size_t *end_ref)
// {
// 	*start_ref = star_case_set_beginning(string, offset_ref);
// 	*end_ref = star_case_set_end(string, offset_ref);
// 	if (string[*end_ref])
// 		*offset_ref = *end_ref + 1;
// 	else
// 		*offset_ref = *end_ref;
// 	return (e_true);
// }
	// *offset_ref = skip_consecutive_chars(string, *offset_ref, '*', +1);
	// while (e_true)
	// {
	// 	if (string[*offset_ref] == '\''
	// 		|| string[*offset_ref] == '"')
	// 	{
	// 		*offset_ref = skip_consecutive_chars(string, *offset_ref, string[*offset_ref]);
	// 		*offset_ref = skip_past_last_char(string, *offset_ref, string[*offset_ref], +1);
	// 	}
	// 	if (e_true == bash_control_character(string[*offset_ref]))
	// 		break ;
	// }
	// if (string[*offset_ref] == '/')
	// {
	// 	while (string[*offset_ref]
	// 			&& e_false == bash_control_character(string[*offset_ref]))
	// 			*offset_ref += 1;
	// 	// *offset_ref = skip_consecutive_chars(string, *offset_ref + 1, '*');
	// 	return (e_false);
	// }
	// else
	// {
	// 	// *offset_ref -= 1;
	// 	star_expansion_segment_set_boundaries(string, *offset_ref - 1, start_ref, end_ref);
	// 	*offset_ref = *end_ref;
	// 	return (e_true);
	// }

t_bool	dollar_case(char *string, size_t *offset_ref,
			size_t *start_ref, size_t *end_ref)
{
	*start_ref = *offset_ref;
	*offset_ref += 1;
	if (string[*offset_ref] == '*')
		*end_ref = *offset_ref;
	else
	{
		while (e_true)
		{
			if (string[*offset_ref] == '$'
				|| string[*offset_ref] == '*')
				break ;
			if (string[*offset_ref] == '\0'
				|| e_true == bash_control_character(string[*offset_ref]))
				break ;
			*offset_ref += 1;
		}
		*end_ref = *offset_ref - 1;
	}
	return (e_true);
}

// static void	star_expansion_segment_set_boundaries(char *string, size_t special_char_pos,
// 			size_t *start_ref, size_t *end_ref)
// {
// 	*start_ref = star_expansion_segment_set_part(string, special_char_pos, -1);
// 	*end_ref = star_expansion_segment_set_part(string, special_char_pos, +1);
// }

// static size_t	star_expansion_segment_set_part(char *string, size_t special_char_pos,
// 		int increment)
// {
// 	int	point;

// 	if (special_char_pos + increment < 0
// 		|| string[special_char_pos + increment] == '\0')
// 		return (special_char_pos);
// 	point = special_char_pos + increment;
// 	while (e_true)
// 	{
// 		if (string[point] == '"' || string[point] == '\'')
// 		{
// 			point = skip_past_last_char(string, point + increment,
// 						string[point], increment);
// 		}
// 		if (e_true == bash_control_character(string[point])) // || string[point] == '*')
// 			return (point - increment);
// 		if (point == 0 || string[point + increment] == '\0')
// 			return (point);
// 		point += increment;
// 	}
// 	return (-1);
// }
