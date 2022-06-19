/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 22:32:41 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

char	*scan_var_name(char *cursor, char **name)
{
	char	*name_cursor;
	size_t	name_len;

	if (e_false == ft_is_alpha(*cursor) && *cursor != '_')
		return (NULL);
	name_cursor = cursor + 1;
	while (*name_cursor
		&& (char_is_alpha(*name_cursor)
			|| char_is_digit(*name_cursor)
			|| *name_cursor == '_')
		)
		name_cursor++;
	if (*name_cursor
		&& e_false == bash_control_character(*name_cursor)
		&& *name_cursor != '=')
		return (NULL);
	name_len = ft_strlen(cursor) - ft_strlen(name_cursor);
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	(*name)[name_len] = '\0';
	ft_strcpy(*name, cursor, name_len);
	return (name_cursor);
}

char	*scan_var_value(char *cursor, char **value)
{
	char	*value_cursor;
	size_t	value_len;

	value_cursor = cursor;
	if (*value_cursor != "=")
		return (NULL);
	value_cursor++;
	if (*value_cursor == '"' || *value_cursor == '\'')
		return (ft_substr(value_cursor + 1, *value_cursor));
	value_len = 0;
	while (value_cursor[value_len])
	{
		if (e_true == bash_control_character(value_cursor[value_len]))
				break ;
		value_len++;
	}
	if (value_len == 0)
		return (NULL);
	// value_len = ft_strlen(cursor) - ft_strlen(value_cursor);
	(*value) = (char *) malloc((value_len + 1) * sizeof(char));
	(*value)[value_len] = '\0';
	ft_strcpy((*value), cursor, value_len);
	return (value_cursor);
}

static void	*lexer_input_handling(void *arg, char **input_string_ref,
			int *offset, t_op_code op_code)
{
	if (op_code == e_STORE_STR && *offset > -1)
	{
		*input_string_ref = (char *)arg;
		*offset = 0;
	}
	else if (op_code == e_ADVANCE_STR && *offset > -1)
	{
		*offset = range_spill(
				*offset + *((int *)arg),
				ft_strlen(*input_string_ref),
				0, -1
				);
		if (*offset == -1)
			free(*input_string_ref);
	}
	else if (op_code == e_RETURN_CUR_STR && *offset > -1)
	{
		return (*input_string_ref + *offset);
	}
	return (NULL);
}

static void	*lexer_token_handling(void *arg, t_token **cur_token,
			t_op_code op_code)
{
	if (op_code == e_STORE_NXT_TOK)
	{
		ft_free(*cur_token);
		*cur_token = (t_token *)arg;
		return (NULL);
	}
	else if (op_code == e_RETURN_TOK)
	{
		return (*cur_token);
	}
	return (NULL);
}

// ! to DECOMMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	*lexer(void *arg, t_op_code op_code)
{
	static char		*__input_string = NULL;
	static int		offset = -1;
	static t_token	*cur_token = NULL;

	if (op_code == e_CLEAN)
	{
		ft_free(__input_string);
		__input_string = NULL;
		ft_free(cur_token);
		cur_token = NULL;
		offset = -1;
	}
	if (op_code == e_STORE_STR || op_code == e_RETURN_CUR_STR
		|| op_code == e_ADVANCE_STR)
		return (lexer_input_handling(arg,
				&__input_string, &offset, op_code));
	else if (op_code == e_STORE_NXT_TOK || op_code == e_RETURN_TOK)
		return (lexer_token_handling(arg,
				&cur_token, op_code));
	return (NULL);
}
