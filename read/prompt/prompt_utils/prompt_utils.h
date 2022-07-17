/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:04:09 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 18:43:12 by mmarinel         ###   ########.fr       */
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


char		**ft_add_history(char *command);

#endif