/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_module.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 18:33:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_MODULE_H
# define PRINT_MODULE_H

//* user defined types
# include "../types.h"


//* user defined exposed functions
void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);

#endif