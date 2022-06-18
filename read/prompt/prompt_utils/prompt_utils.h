/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:04:09 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/18 19:05:27 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_UTILS_H
# define PROMPT_UTILS_H

#include "../../read.h"

t_bool	here_doc_line(char *command);
void	here_doc_read(char *delimiter);
char	*here_doc_take_delimiter(char *command);

#endif