/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 13:05:38 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

char	*scan_var_name(char *cursor)
{
	if (e_false == ft_is_alpha(*cursor) && *cursor != '_')
		return (NULL);
	cursor++;
	while (*cursor
		&& (char_is_alpha(*cursor)
			|| char_is_digit(*cursor)
			|| *cursor == '_')
		)
		cursor++;
	return (cursor);
}
