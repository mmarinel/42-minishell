/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_grammar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:26:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:34:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

/**
 * @brief this function scans the next word delimited by spaces
 * and consisting of contiguous quoted sequences
 * ending with a bash control character. 
 * (i.e.: a quoted sequence is a sequence of chars delimited by quotes
 * or a single word delimited by bash control characters except quotes)
 * 
 * @param command_line 
 * @param offset current offste inside command line
 * @return size_t the lenght of the next bash word
 */
size_t	bash_next_word_len(char *command_line, size_t offset)
{
	size_t	len_word;

	offset = skip_consecutive_chars(command_line, offset, ' ', +1);
	{
		len_word = 0;
		while (command_line[offset + len_word])
		{
			while (ft_is_quote(command_line[offset + len_word]))
					len_word = skip_past_char(
						command_line + offset,
						len_word + 1,
						command_line[offset + len_word],
						+1);
			if (command_line[offset + len_word] == '\0'
				|| e_true == bash_control_character(
					command_line[offset + len_word]))
				break ;
			len_word++;
		}
		return (len_word);
	}
}

/**
 * @brief this function takes the len of the next bash string
 * (i.e.: a string delimiting by bash control characters other than '$'
 * or end/start of string).
 * 
 * @param str 
 * @param offset 
 * @return size_t 
 */
size_t	bash_next_string_len(char *str, size_t offset)
{
	size_t	bash_string_len;
	int		new_offset;
	t_bool	repeat;

	new_offset = offset;
	{
		repeat = e_true;
		while (repeat)
		{
			new_offset = skip_consecutive_chars(str, new_offset, '$', +1);
			new_offset += bash_next_word_len(str, new_offset);
			if (str[new_offset] != '$')
				repeat = e_false;
		}
		bash_string_len = new_offset - offset;
	}
	return (bash_string_len);
}

t_bool	is_env_var_name(char *str)
{
	size_t	offset;

	if (str == NULL
		|| (e_false == char_is_alpha(str[0]) && '_' != str[0]))
		return (e_false);
	offset = 1;
	while (str[offset])
	{
		if (e_false == char_is_alpha(str[offset])
			&& e_false == char_is_digit(str[offset])
			&& '_' != str[offset])
			return (e_false);
		offset += 1;
	}
	return (e_true);
}

t_bool	bash_word_is_empty(char *command)
{
	size_t	offset;

	if (!command)
		return (e_true);
	offset = 0;
	while (command[offset])
	{
		if (e_false == ft_isspace(command[offset]
				&& e_false == ft_is_quote(command[offset])))
			return (e_false);
		offset++;
	}
	return (e_true);
}

t_bool	command_is_empty(char *command)
{
	size_t	offset;

	if (!command)
		return (e_true);
	offset = 0;
	while (command[offset])
	{
		if (e_false == ft_isspace(command[offset]))
			return (e_false);
		offset++;
	}
	return (e_true);
}
