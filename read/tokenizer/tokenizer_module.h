/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_module.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:18:06 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 08:51:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_MODULE_H
# define TOKENIZER_MODULE_H

# include "tok_types.h"

void	tokenizer_feed_input(char *command_line);
t_token	*next_token(void);
void	tokenizer_free(void);

char *tok_to_string(t_token *token);
void	print_token(t_token *token);

#endif