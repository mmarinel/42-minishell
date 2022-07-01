/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_module.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:18:06 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 16:07:15 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_MODULE_H
# define TOKENIZER_MODULE_H

# include "tok_types.h"

void	tokenizer_feed_input(char *command_line);
t_token	*cur_token(void);
t_token	*next_token(void);

char *tok_to_string(t_token *token);

#endif