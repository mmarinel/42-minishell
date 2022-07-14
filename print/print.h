/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 18:37:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

//* system libraries
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//* user defined types
# include "../colors.h"
# include "../types.h"


//* user defined exposed functions
void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);

#endif