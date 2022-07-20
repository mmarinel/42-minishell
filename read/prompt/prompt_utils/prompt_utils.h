/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:04:09 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 09:18:47 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_UTILS_H
# define PROMPT_UTILS_H


// * standard libraries
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>

// * user defined 
# include "../../../global.h"
# include "../../../types.h"
# include "../../../colors.h"
# include "../../../utils/ft_utils.h"
# include "../../../signals/signal_module.h"
# include "../prompt_types.h"


// * user defined module
# include "../../../exit/exit.h"

// * includes end //


/**
 * @brief this function reads a non-empty line using the readline library function.
 * If ctrl-d is hit it returns NULL.
 * 
 * @param prompt 
 * @return char* 
 */
char		*ft_readline(char *prompt);
char		**ft_add_history(char *command);
char		*tee_wrap_command(char *command);

#endif