/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:52:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 09:30:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TYPES_H
# define PRINT_TYPES_H

typedef enum e_printer_opcode
{
	GET_STDOUT_BYTE_SHIFT,
	CALCULATE_STDOUT_BYTE_SHIFT
}	t_print_opcode;

typedef enum e_stdout_to_dump
{
	STDOUT_2_DUMP,
	STDOUT_RESTORE
}	t_stdout_to_dump;

#endif