/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_clear.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:58:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:59:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

static size_t	results_count_entries(char **results);
//* end of static declarations

char	**clean_results(char **results)
{
	char	**cleared;
	size_t	count;
	size_t	i;
	size_t	j;

	count = results_count_entries(results);
	cleared = (char **) malloc((count + 1) * sizeof(char *));
	cleared[count] = NULL;
	i = 0;
	j = 0;
	while (results[i])
	{
		if ('\0' != *(results[i]))
		{
			cleared[j] = ft_strcpy(NULL, results[i], ft_strlen(results[i]));
			j++;
		}
		i++;
	}
	ft_splitclear(results);
	return (cleared);
}

static size_t	results_count_entries(char **results)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (results[i])
	{
		if ('\0' != *(results[i]))
			count++;
		i++;
	}
	return (count);
}
