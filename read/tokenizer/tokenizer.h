/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 14:52:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../read.h"
# include "../read_utils/read_utils.h"
# include "tok_patterns/tok_patterns.h"
# include "tok_utils/tok_utils.h"
# include "tok_types.h"

// * user defined exposed function

void	tokenizer_feed_input(char *command_line);
t_token	*next_token(void);
void	tok_go_back(void);

#endif