/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 16:16:19 by mmarinel         ###   ########.fr       */
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

//* user defined modules //
# include "../../error_handling/error_handling_module.h"

// * start of declarations //

void	scan(char *command_line, t_token **tok_list_ref);

#endif