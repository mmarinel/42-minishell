/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns_granular_part1.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:56:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 16:22:45 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_granular.h"

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

	pre_offset = scan_invariants(str, offset);
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
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	// printf(YELLOW "malloc in tok_var_patterns_granular_part1.c line 41: %p\n" RESET, *name);
	// fflush(stdout);
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
		return (offset + 2 + ft_strlen(*value) + 1);
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
	// printf(YELLOW "malloc in tok_var_patterns_granular_part1.c line 77: %p\n" RESET, *value);
	// fflush(stdout);
	(*value)[value_len] = '\0';
	ft_strcpy((*value), str + offset + 1, value_len);
	return (offset + 1 + value_len);
}

size_t	scan_var_mode(char *command_line, size_t offset, t_bool *concat_mode)
{
	if (command_line[offset] == '+')
	{
		*concat_mode = e_true;
		return (offset + 1);
	}
	else
	{
		*concat_mode = e_false;
		return (offset);
	}
}

size_t	scan_var(char *str, size_t offset,
			t_token_id tok_type, t_bindings **next_var)
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
	new_offset = scan_var_name(str, offset, &var_name);
	if (!var_name)
		return (offset);
	if (tok_type == e_ENV_VAR_DECL)
		new_offset = scan_var_value(str, new_offset, &var_value, &concat_mode);
	*next_var = (t_bindings *) malloc(sizeof(t_bindings));
	// printf(YELLOW "malloc in tok_var_patterns_granular_part1.c line 116: %p\n" RESET, *next_var);
	// fflush(stdout);
	(*next_var)->var_name = var_name;
	(*next_var)->var_val = var_value;
	(*next_var)->concat_mode = concat_mode;
	(*next_var)->prev = NULL;
	return (new_offset);
}
