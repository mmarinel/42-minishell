/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:56:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 10:54:34 by mmarinel         ###   ########.fr       */
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
	new_offset = scan_spaces(str,  offset);
	new_offset = scan_invariant_quotes(str, offset);
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
size_t	scan_var_name(char *str, size_t offset, char **name)
{
	size_t	pre_offset;
	size_t	name_len;

	pre_offset = scan_spaces(str, offset);
	pre_offset = scan_invariant_quotes(str, pre_offset);
	pre_offset = scan_export_keyword(str, pre_offset);
	pre_offset = scan_spaces(str, offset);
	pre_offset = scan_invariant_quotes(str, pre_offset);
	if (e_false == char_is_alpha(str[pre_offset]) && str[pre_offset] != '_')
		return (offset);
	name_len = 0;
	while (str[pre_offset + name_len]
		&& (char_is_alpha(str[pre_offset + name_len])
			|| char_is_digit(str[pre_offset + name_len])
			|| str[pre_offset + name_len] == '_')
		)
		name_len++;
	if (str[pre_offset + name_len] != '\0'
		&& e_false == bash_control_character(str[pre_offset + name_len])
		&& str[pre_offset + name_len] != '=')
		return (offset);
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	(*name)[name_len] = '\0';
	ft_strcpy(*name, str + pre_offset, name_len);
	return (pre_offset + name_len);
}

/**
 * @brief <=><quoted argument with any character | anything unquoted except bash control characters>
 * 
 * @param cursor 
 * @param value 
 * @return char* 
 */
size_t	scan_var_value(char *str, size_t offset, char **value)
{
	size_t	value_len;

	if (str[offset] != '=')
		return (offset);
	if (str[offset + 1] == '"' || str[offset + 1] == '\'')
	{
		*value = ft_substr(str + (offset + 2), str[offset + 1]);
		return (offset + 2 + ft_strlen(*value));
	}
	value_len = 0;
	while (str[offset + 1 + value_len])
	{
		if (e_true == bash_control_character(str[offset + 1 + value_len]))
				break ;
		value_len++;
	}
	if (value_len == 0)
		return (offset);
	// value_len = ft_strlen(cursor) - ft_strlen(value_cursor);
	(*value) = (char *) malloc((value_len + 1) * sizeof(char));
	(*value)[value_len] = '\0';
	ft_strcpy((*value), str + offset + 1, value_len);
	return (offset + 1 + value_len);
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
	pre_offset = scan_var_name(str, pre_offset, &var_name);
	if (!var_name)
		return (offset);
	pre_offset = scan_var_value(str, pre_offset, &var_value);
	*next_var = (t_var_ass_content *) malloc(sizeof(t_var_ass_content));
	(*next_var)->name = var_name;
	(*next_var)->val = var_value;
	// printf("name is:%sJ\nvalue is:%sJ\n", var_name, var_value);
	// exit(0);
	return (pre_offset);
}
