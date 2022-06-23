/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:56:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 09:25:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_utils.h"

// int	scan_spaces(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (e_true == ft_isspace(str[idx]))
// 		idx++;
// 	return (idx);
// }

// int	scan_invariant_quotes(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (str[idx] == '"' || str[idx] == '\'')
// 	{
// 		if (str[idx + 1] != str[idx])
// 			break ;
// 		idx += 2;
// 	}
// 	return (idx);
// }

int	scan_export_keyword(char *str, size_t offset)
{
	int	new_offset;

	new_offset = offset;
	new_offset += scan_spaces(str + offset);
	new_offset += scan_invariant_quotes(str + offset);
	if (str[new_offset] != '\0'
		&& ft_strncmp(str + new_offset, "export", 6 * sizeof(char)) == 0)
		return (new_offset + 6);
	return (offset);
}

/**
 * @brief <spaces><closed_quotes>name<space|control character|eof|=>
 * 
 * @param cursor 
 * @param name 
 * @return char* 
 */
size_t	scan_var_name(char *cursor, char **name)
{
	size_t	name_cursor;
	size_t	name_len;

	name_cursor = scan_spaces(cursor);
	name_cursor += scan_invariant_quotes(cursor + name_cursor);
	if (cursor[name_cursor] == '\0'
		|| ft_strncmp(cursor + name_cursor, "export", 6 * sizeof(char)) != 0)
		return (0);
	name_cursor += 6;
	name_cursor += scan_spaces(cursor + name_cursor);
	name_cursor += scan_invariant_quotes(cursor + name_cursor);
	if (e_false == char_is_alpha(cursor[name_cursor]) && cursor[name_cursor] != '_')
		return (0);
	name_len = 0;
	while (cursor[name_cursor + name_len]
		&& (char_is_alpha(cursor[name_cursor + name_len])
			|| char_is_digit(cursor[name_cursor + name_len])
			|| cursor[name_cursor + name_len] == '_')
		)
		name_len++;
	if (cursor[name_cursor + name_len] != '\0'
		&& e_false == ft_isspace(cursor[name_cursor + name_len])
		&& e_false == bash_control_character(cursor[name_cursor + name_len])
		&& cursor[name_cursor + name_len] != '=')
		return (0);
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	(*name)[name_len] = '\0';
	ft_strcpy(*name, cursor + name_cursor, name_len);
	return (name_cursor);
}

/**
 * @brief <=><quoted argument with any character | anything unquoted except bash control characters>
 * 
 * @param cursor 
 * @param value 
 * @return char* 
 */
size_t	scan_var_value(char *cursor, char **value)
{
	size_t	value_cursor;
	size_t	value_len;

	value_cursor = 0;
	if (cursor[value_cursor] != '=')
		return (0);
	value_cursor++;
	if (cursor[value_cursor] == '"' || cursor[value_cursor] == '\'')
		return (ft_strlen(cursor)
			- ft_strlen(ft_substr(cursor + (value_cursor + 1), cursor[value_cursor]))
		);
	value_len = 0;
	while (cursor[value_cursor + value_len])
	{
		if (e_true == bash_control_character(cursor[value_cursor + value_len]))
				break ;
		value_len++;
	}
	if (value_len == 0)
		return (0);
	// value_len = ft_strlen(cursor) - ft_strlen(value_cursor);
	(*value) = (char *) malloc((value_len + 1) * sizeof(char));
	(*value)[value_len] = '\0';
	ft_strcpy((*value), cursor + value_cursor, value_len);
	return (value_cursor);
}

size_t	scan_var(char *str, size_t offset, t_var_ass_content **next_var)
{
	char				*var_name;
	char				*var_value;
	size_t				pre_offset;

	if (!str[offset])
		return (offset);
	var_name = NULL;
	var_value = NULL;
	pre_offset = scan_export_keyword(str, offset);
	pre_offset += scan_var_name(str + pre_offset, &var_name);
	if (!var_name)
		return (offset);
	pre_offset += scan_var_value(str + pre_offset, &var_value);
	*next_var = (t_var_ass_content *) malloc(sizeof(t_var_ass_content));
	(*next_var)->name = var_name;
	(*next_var)->val = var_value;
	return (pre_offset + offset);
}
