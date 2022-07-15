/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:52:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 10:53:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TYPES_H
# define PRINT_TYPES_H

typedef enum e_printer_opcode
{
	GET_STDOUT_BYTE_SHIFT,
	PRINT
}	t_print_opcode;

#endif