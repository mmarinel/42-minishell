/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:36:03 by earendil          #+#    #+#             */
/*   Updated: 2022/08/11 19:12:57 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

static void	take_next_segment_boundaries(char *str,
				size_t *start, size_t *end);
static void	take_boundaries_general_case(char *str,
				size_t *start, size_t *end);
static char	*get_segment(char *str,
				size_t start, size_t end);
static char	*get_suffix(char *str, size_t cutting_index);
//* end of static declarations

void	expansion_split(
				char *args,
				char **next_segment_ref,
				char **post_ref)
{
	size_t	start_of_segment;
	size_t	end_of_segment;

	take_next_segment_boundaries(args,
		&start_of_segment, &end_of_segment);
	*next_segment_ref = get_segment(args, start_of_segment, end_of_segment);
	*post_ref = get_suffix(args, end_of_segment + 1);
}

static void	take_next_segment_boundaries(char *str,
				size_t *start, size_t *end)
{
	size_t	offset;

	if (!str || !str[0])
		return ;
	{
		*start = 0;
		if (str[0] == '$' && str[1] == '*')
			*end = 1;
		else if (str[0] == '$' && str[1] == '$')
			*end = 1;
		else if (str[0] == '$' && ft_is_quote(str[1]))
		{
			*start = 1;
			*end = skip_past_char(str, 2, str[1], +1) - 1;
		}
		else if (e_true == ft_isspace(str[0]))
			*end = skip_consecutive_chars(str, 1, str[0], +1) - 1;
		else
			take_boundaries_general_case(str, start, end);
	}
}

static void	take_boundaries_general_case(char *str,
				size_t *start, size_t *end)
{
	size_t	offset;

	*start = 0;
	offset = 0;
	if (str[offset] == '"' || str[offset] == '\'')
		offset = skip_past_char(str, offset + 1, str[offset], +1) - 1;
	while (str[offset + 1]
		&& str[offset + 1] != '$'
		&& e_false == bash_control_character(str[offset + 1]))
		offset++;
	*end = offset;
}

static char	*get_segment(char *str,
				size_t start, size_t end)
{
	if (start > end)
		return (NULL);
	else
		return (ft_strcpy(NULL, str + start, end - start + 1));
}

static char	*get_suffix(char *str, size_t cutting_index)
{
	size_t	len_str;

	len_str = ft_strlen(str);
	if (cutting_index > len_str - 1)
		return (NULL);
	else
		return (ft_strcpy(NULL, str + cutting_index,
				len_str - cutting_index));
}
