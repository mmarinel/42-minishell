/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:04:09 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 10:04:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_UTILS_H
# define PROMPT_UTILS_H


// * standard libraries
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

// * user defined 
# include "../../../types.h"
# include "../../../colors.h"
# include "../../../utils/ft_utils.h"


// * user defined module
# include "../../../exit/exit.h"

// * includes end //


char	**ft_add_history(char *command);

t_bool	here_doc_line(char *command);
void	here_doc_read(char *command);

#endif