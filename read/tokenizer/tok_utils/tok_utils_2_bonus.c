/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:36:08 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/21 17:30:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

/**
 * @brief <spaces><closed_quotes>name<space|control character|eof|=>
 * 
 * @param cursor 
 * @param name 
 * @return char* 
 */
char	*scan_var_name(char *cursor, char **name)
{
	char	*name_cursor;
	size_t	name_len;

	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (!(*cursor)
		|| ft_strncmp(cursor, "export", 6 * sizeof(char)) != 0)
		return (NULL);
	cursor = cursor + 6;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (e_false == ft_is_alpha(*cursor) && *cursor != '_')
		return (NULL);
	name_cursor = cursor;
	while (*name_cursor
		&& (char_is_alpha(*name_cursor)
			|| char_is_digit(*name_cursor)
			|| *name_cursor == '_')
		)
		name_cursor++;
	if (*name_cursor != '\0'
		&& e_false == ft_isspace(*name_cursor)
		&& e_false == bash_control_character(*name_cursor)
		&& *name_cursor != '=')
		return (NULL);
	name_len = ft_strlen(cursor) - ft_strlen(name_cursor);
	*name = (char *) malloc((name_len + 1) * sizeof(char));
	(*name)[name_len] = '\0';
	ft_strcpy(*name, cursor, name_len);
	return (name_cursor);
}

/**
 * @brief <=><quoted argument with any character | anything unquoted except bash control characters>
 * 
 * @param cursor 
 * @param value 
 * @return char* 
 */
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

int	scan_env_var(char *str)
{
	char	*cursor;

	if (!str)
		return (-1);
	cursor = str;
	cursor += scan_spaces(cursor);
	cursor += scan_invariant_quotes(cursor);
	if (!cursor || ft_strncmp(cursor, "export", 6 * sizeof(char)))
		return (-1);
	return ((ft_strlen(str) - ft_strlen(cursor)) + scan_var(cursor + 6, e_ENV_VAR_ASSIGN));
}

t_var_ass_content	*scan_var_set_cursor(char *str, char **cursor)
{
	t_var_ass_content	*var;

	if (!str || !(*str))
		return (-1);
	var = (t_var_ass_content *) malloc(sizeof(t_var_ass_content));
	var->name = scan_var_name(str, cursor);
	if (!(var->name))
	{
		ft_free(var);
		return (NULL);
	}
	var->val = scan_var_value(str, &cursor);
	// token->token_val = (t_var_content *) malloc(sizeof(t_var_content));
	// ((t_var_content *)(token->token_val))->name = var_name;
	// ((t_var_content *)(token->token_val))->val = var_value;
	/*	= string_strip(
			string_strip(var_value, '"', e_true),
			'\'', e_true); */
	return (var);
}

int	scan_var(char *str)
{
	int					new_offset;
	t_var_ass_content	*next_var;
	t_token				*token;

	new_offset = 0;
	token = NULL;
	while (e_true)
	{
		next_var = scan_var_set_cursor(str, &cursor, var_type);
		if (!next_var)
			break ;
		if (!token)
		{
			token = (t_token *) malloc(sizeof(t_token));
			token->token_id =  e_ENV_VAR_ASSIGN;
		}
		next_var->next = token->token_val;
		token->token_val =  next_var;
	}
	new_offset = ft_strlen(str) - ft_strlen(cursor); // + 1;
	if (token)
		lexer(token, e_STORE_NXT_TOK);
	return (new_offset);
}

int	scan_alternate_invariant_spaces_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		// READING ALL INVARIANT QUOTES
		while (str[idx] == '"' || str[idx] == '\'')
		{
			if (str[idx + 1] != str[idx])
				break ;
			idx += 2;
		}
		// READING ALL FINAL SPACES
		while (str[idx])
		{
			if (e_false == ft_isspace(str[idx]))
				break ;
			idx++;
		}
		if (str[idx] != '"' && str[idx] != '\''
			&& e_false == ft_isspace(str[idx]))
			break ;
	}
	return (idx);
}

int	scan_spaces(char *str)
{
	int	idx;

	idx = 0;
	while (e_true == ft_isspace(str[idx]))
		idx++;
	return (idx);
}

int	scan_invariant_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] == '"' || str[idx] == '\'')
	{
		if (str[idx + 1] != str[idx])
			break ;
		idx += 2;
	}
	return (idx);
}
