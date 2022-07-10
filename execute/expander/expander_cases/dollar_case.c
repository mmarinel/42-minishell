/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:49:32 by earendil          #+#    #+#             */
/*   Updated: 2022/07/09 19:50:23 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_cases.h"

char	*expand_dollar_case(char *args)
{
	char	*args_pre;
	char	*next_segment;
	char	*args_post;

	if (!args)
		return (NULL);
	expansion_split(STAR, args, &next_segment, &args_post);
	free(args);
	return (
		ft_strjoin(
			ft_strjoin(args_pre, expand_star_segment(next_segment),
				e_true, e_true),
			expand_dollar_case(args_post),
			e_true, e_true
		)
	);
}
