/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:07:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/16 17:21:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, t_bool go_on_newline)
{
	if (go_on_newline == e_true)
		; // printf("\n"); // ! Only on Linux !!!
	exit(exit_status);
}
