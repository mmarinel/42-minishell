/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:57:06 by evento            #+#    #+#             */
/*   Updated: 2022/07/11 19:41:44 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TYPES_H
# define SIGNAL_TYPES_H

typedef enum e_sig_handling_opcode
{
	SIG_INITIAL,
	SIG_AT_EXIT
}	t_sig_handling_opcode;

#endif