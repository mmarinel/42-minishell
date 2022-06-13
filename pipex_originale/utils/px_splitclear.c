/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_splitclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:02:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/20 10:01:51 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"

void	*px_splitclear(char **split)
{
	char	**temp;

	if (!split)
		return (NULL);
	temp = split;
	while (temp && *temp)
		px_free(*temp++);
	px_free(split);
	return (NULL);
}
