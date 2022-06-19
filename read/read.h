/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 13:09:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "../includes.h"
# include "prompt/prompt.h"
# include "read_utils/read_utils.h"
# include "tokenizer/tokenizer.h"

// * user defined EXPOSED FUNCTIONS

char	*shell_read( char *const envp[]);

#endif