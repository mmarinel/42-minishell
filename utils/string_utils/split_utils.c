/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:59:11 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:45:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

void	*ft_splitclear(char **split)
{
	size_t	i;
	char	**backup;

	if (!split)
		return (NULL);
	{
		backup = split;
		i = 0;
		while (split[i])
		{
			ft_free(split[i]);
			i++;
		}
		ft_free(backup);
	}
	return (NULL);
}

char	*split_merge(char	**split, char *const sep, t_bool free_split)
{
	char	*merge;
	size_t	i;

	if (!split)
		return (NULL);
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

size_t	split_len(char **split)
{
	size_t	i;

	if (split == NULL)
		return (0);
	else
	{
		i = 0;
		while (split[i])
			i++;
		return (i);
	}
}
