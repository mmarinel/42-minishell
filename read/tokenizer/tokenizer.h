/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 09:39:50 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// * standard libraries //
# include <stdlib.h>

// * types //
# include "../../global.h"
# include "tok_types.h"

// * user defined helper functions
# include "../../utils/ft_utils.h"

// * SUBMODULES //
# include "tok_patterns/tok_patterns.h"
# include "tok_utils/tok_utils.h"


// * start of declarations //

void	tokenizer_feed_input(char *command_line);
t_token	*next_token(void);
void	tokenizer_free(void);

#endif