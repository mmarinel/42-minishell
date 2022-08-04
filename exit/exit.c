/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:07:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 16:12:58 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	print_exit_to_real_stdout(void);
static void	clear_last_history_entry(void);

// * end of static declarations //

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status)
{
	print_exit_to_real_stdout();
	clear_last_history_entry();
	rl_clear_history();
	sig_handling_set(SIG_AT_EXIT);
	// ft_unlink(get_stdout_dump_file_name(), e_true);
	//* clear_all();
	exit(exit_status);
}

static void	print_exit_to_real_stdout(void)
{
	int	cur_stdout_backup;

	cur_stdout_backup = dup(STDOUT_FILENO);
	dup2(g_env.stdout_clone, STDOUT_FILENO);
	ft_printf("%s", "exit\n");
	dup2(cur_stdout_backup, STDOUT_FILENO);
	close(cur_stdout_backup);
}

static void	clear_last_history_entry(void)
{
	ft_free(*ft_add_history(NULL));
}
