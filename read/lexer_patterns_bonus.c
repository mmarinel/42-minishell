/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 08:53:18 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

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
