/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 11:00:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

//* system libraries
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//* user defined types
# include "print_types.h"
# include "../colors.h"
# include "../types.h"

//* user defined modules
# include "../get_next_line/get_next_line.h"

//* user defined exposed functions
void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);

#endif