/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:09:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/29 09:09:43 by mmarinel         ###   ########.fr       */
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
