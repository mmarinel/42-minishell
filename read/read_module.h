/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_module.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:37:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:48:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_MODULE_H
# define READ_MODULE_H

// * user defined submodules //
# include "prompt/prompt_module.h"
# include "tokenizer/tokenizer_module.h"
# include "parser/parser_module.h"

t_tree_node	*shell_read(void);

#endif