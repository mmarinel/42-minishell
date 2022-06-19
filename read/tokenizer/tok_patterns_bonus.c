/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 18:08:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	scan_arg(char **str)
{
}

int	scan_name(char **str, t_op_code	*possible_names)
{
	int	new_offset;

	if (*possible_names == e_NONE)
		return (-1);
	new_offset = scan(&str, *possible_names);
	if (new_offset == -1)
		return (scan_name(str, possible_names + 1));
	else
		return (new_offset);
}

t_token	*scan_shell_var(char *str)
{
	char	*cursor;
	char	*scanned;
	size_t	scanned_len;
	int		i;

	cursor = scan_var_name(str);
	if (!cursor)
		return (NULL);
	if (*cursor == "=")
	{

	}
	scanned_len = ft_strlen(str) - ft_strlen(cursor);
	scanned = (char *) malloc(sizeof(char) * scanned_len);
	i = -1;
	while (++i < scanned_len)
		scanned[i] = str[i];
	scanned[scanned_len] = '\0';
	return (scanned);
}
