/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cases.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:43:48 by earendil          #+#    #+#             */
/*   Updated: 2022/08/10 10:50:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASES_H
# define CASES_H

# include "../expander.h"

// * cases //
char	*expand_dollar_segment(char *next_segment,
				char containing_sequence);
char	*expand_star_segment(char *segment, char containing_sequence);
// char	*expand_star_case(char *args, t_seg_sequence seg_sequence);
// char	*expand_dollar_case(char *args, t_seg_sequence seg_sequence);


#endif