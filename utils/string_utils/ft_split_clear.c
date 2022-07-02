/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:59:11 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 19:50:58 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

void	*ft_splitclear(char **split)
{
	char	**backup;

	if (!split)
		return (NULL);
	backup = split;
	while (*split)
		ft_free(*split++);
	ft_free(backup);
	return (NULL);
}
