/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_continuation_prompt.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:26:28 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 16:28:43 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_CONTINUATION_PROMPT_H
# define LINE_CONTINUATION_PROMPT_H

# include "../prompt.h"

void	line_continuation_prompt(t_prompt_behav opcode,
			int line_channel[2], int line_size_channel[2]);

#endif