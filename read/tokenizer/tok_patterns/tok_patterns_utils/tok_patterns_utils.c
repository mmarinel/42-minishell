/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:56:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/24 15:00:42 by mmarinel         ###   ########.fr       */
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

	new_offset = scan_invariants(str, offset);
	if (str[new_offset] != '\0'
		&& ft_strncmp(str + new_offset, "export", 6) == 0)
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
	if (e_false == char_is_alpha(str[pre_offset]) && str[pre_offset] != '_')
		return (offset);
	name_len = 0;
	while (str[pre_offset + name_len]
		&& (
			char_is_alpha(str[pre_offset + name_len])
			|| char_is_digit(str[pre_offset + name_len])
			|| str[pre_offset + name_len] == '_'
		)
	)
		name_len++;
	if (str[pre_offset + name_len] != '\0'
		&& e_false == bash_control_character(str[pre_offset + name_len])
		&& str[pre_offset + name_len] != '='
		&& str[pre_offset + name_len] != '+')
		return (offset);
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	(*name)[name_len] = '\0';
	ft_strcpy(*name, str + pre_offset, name_len);
	return (pre_offset + name_len);
}

/**
 * @brief <=><quoted argument with any character
 * | anything unquoted except bash control characters>
 * 
 * @param cursor 
 * @param value 
 * @return char* 
 */
size_t	scan_var_value(char *str, size_t offset, char **value,
	t_bool *concat_mode)
{
	size_t	value_len;

	if ((str[offset] != '+' && str[offset] != '=')
		|| (str[offset] == '+' && str[offset + 1] != '='))
		return (offset);
	offset = scan_var_mode(str, offset, concat_mode);
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
		return (offset + 1);
	(*value) = (char *) malloc((value_len + 1) * sizeof(char));
	(*value)[value_len] = '\0';
	ft_strcpy((*value), str + offset + 1, value_len);
	return (offset + 1 + value_len);
}

size_t	scan_var(char *str, size_t offset, t_var_ass_content **next_var)
{
	char				*var_name;
	char				*var_value;
	t_bool				concat_mode;
	size_t				new_offset;

	if (!str[offset])
		return (offset);
	concat_mode = e_false;
	var_name = NULL;
	var_value = NULL;
	// new_offset = scan_inout_file(str, offset, NULL); // ! considerare le redirection subito dopo export?
	new_offset = scan_var_name(str, offset, &var_name);
	if (!var_name)
		return (offset);
	new_offset = scan_var_value(str, new_offset, &var_value, &concat_mode);
	*next_var = (t_var_ass_content *) malloc(sizeof(t_var_ass_content));
	(*next_var)->name = var_name;
	(*next_var)->val = var_value;
	(*next_var)->concat_mode = concat_mode;
	return (new_offset);
}

size_t	scan_next_cmd_arg(char *command_line, size_t offset,
			char **cur_arg_string, t_token **token_list)
{
	size_t	new_offset;
	size_t	len_cmd_arg;
	char	*next_arg;

	new_offset = scan_invariants(command_line, offset); // * questo lo mettiamo nel chiamante!
	if (e_true == bash_control_character(command_line[new_offset])
		&& e_false == ft_isspace(command_line[new_offset])
		&& e_false == redirect_char(command_line[new_offset]))
		return (offset);
	else if (e_true == redirect_char(command_line[new_offset]))
		new_offset = scan_inout_file(command_line, new_offset, token_list);
	else
	{
		len_cmd_arg = mini_next_word_len(command_line, new_offset);
		next_arg = ft_strjoin(
				ft_strcpy(NULL, command_line + new_offset, len_cmd_arg),
				" ",
				e_true, e_false
				);
		(*cur_arg_string) = ft_strjoin((*cur_arg_string),
				next_arg, e_true, e_true);
		new_offset += len_cmd_arg;
	}
	return (new_offset);
}
