/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cases.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:43:48 by earendil          #+#    #+#             */
/*   Updated: 2022/08/11 18:54:37 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_CASES_H
# define EXPANDER_CASES_H

# include "../expander.h"

// * cases //
char	*expand_dollar_segment(char *next_segment,
			char containing_sequence);
char	*expand_star_segment(char *segment, char containing_sequence);

#endif