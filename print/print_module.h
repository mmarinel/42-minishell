/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_module.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 11:18:05 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_MODULE_H
# define PRINT_MODULE_H

//* user defined types
# include "print_types.h"
# include "../types.h"


//* user defined exposed functions
size_t	printer(t_print_opcode opcode);
void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);

#endif