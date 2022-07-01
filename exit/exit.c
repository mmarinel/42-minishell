/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:07:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 17:50:34 by mmarinel         ###   ########.fr       */
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
	ft_free(*ft_add_history(NULL)); // ! potevo anche fare ft_clear history senza copiare la stringa nella funzione chiamata ft_add_history
	printf("exit\n");
	exit(exit_status);
}

// void	exit_command_subshell(int exit_status, t_tree_node *parse_tree)
// {
// 	// TODO
// }
