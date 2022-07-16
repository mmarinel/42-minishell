/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/16 09:29:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand(char *args)
{
	if (!args || !(*args))
		return (args);
	args = expand_dollar_case(args);
	// args = expand_star_case(args);
	return (args);
}
