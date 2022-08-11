/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 12:26:50 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

size_t	scan_spaces(char *str, size_t offset)
{
	int	idx;

	idx = offset;
	while (e_true == ft_isspace(str[idx]))
		idx++;
	return (idx);
}

size_t	scan_invariant_quotes(char *str, size_t offset)
{
	int	idx;

	idx = offset;
	while (str[idx] == '"' || str[idx] == '\'')
	{
		if (str[idx + 1] != str[idx])
			break ;
		idx += 2;
	}
	return (idx);
}

size_t	scan_invariants(char *str, size_t offset)
{
	size_t	new_offset;

	new_offset = scan_spaces(str, offset);
	new_offset = scan_invariant_quotes(str, new_offset);
	return (new_offset);
}

/**
 * @brief this function finds the number of occurrences 
 * outside quotes for a given char.
 * 
 * @param str 
 * @param to_count 
 * @return size_t 
 */
size_t	occ_outside_quotes(char *str, char to_count)
{
	size_t	occurrences;
	size_t	i;
	char	quote;

	if (NULL == str)
		return (0);
	quote = '\0';
	occurrences = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == to_count && quote == '\0')
			|| (str[i] == to_count && quote == to_count))
			occurrences++;
		if (ft_is_quote(str[i]))
		{
			if (quote && str[i] == quote)
				quote = '\0';
			else if (quote == '\0')
				quote = str[i];
		}
		i++;
	}
	return (occurrences);
}

t_bool	is_env_statement(char *command_line, size_t offset)
{
	size_t	i;
	size_t	len_command_line;

	offset = scan_invariants(command_line, offset);
	i = offset;
	while (command_line[i]
		&& e_false == bash_control_character(command_line[i]))
	{
		if (command_line[i] == '=')
			return (e_true);
		i += 1;
	}
	len_command_line = ft_strlen(command_line + offset);
	if ((ft_strncmp(command_line + offset, "export", 6) == 0
			&& len_command_line >= 6
			&& e_true == ft_isspace(command_line[offset + 6]))
		|| (ft_strncmp(command_line + offset, "unset", 5) == 0
			&& len_command_line >= 5
			&& e_true == ft_isspace(command_line[offset + 5])))
		return (e_true);
	return (e_false);
}
