/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:59:11 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 17:46:28 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

char	*split_merge(char	**split, char *const sep, t_bool free_split)
{
	char	*merge;
	size_t	i;

	merge = NULL;
	i = 0;
	while (split[i])
	{
		if (!merge)
			merge = ft_strdup(split[i]);
		else
			merge = ft_strjoin(
				ft_strjoin(merge, sep, e_true, e_false),
				split[i],
				e_true, e_false
			);
		i++;
	}
	if (free_split)
		ft_splitclear(split);
	return (merge);
}
