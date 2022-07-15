/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:07:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 11:17:42 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	print_message(t_bool ctrl_d);
static size_t	get_prompt_len(void);
static size_t	get_cwd_len(char *cwd);

// * end of static declarations //


/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, t_bool ctrl_d)
{
	print_message(ctrl_d);
	ft_free(*ft_add_history(NULL)); // ! potevo anche fare ft_clear history senza copiare la stringa nella funzione chiamata ft_add_history
	rl_clear_history();
	sig_handling_set(SIG_AT_EXIT);
	// * clear_all();
	exit(exit_status);
}

static void	print_message(t_bool ctrl_d)
{
	size_t	shlvl;
	char	*msg;
	size_t	prompt_len;

	if (e_false == ctrl_d)
	{
		shlvl = atoi(env_handler(BINDING_GET_VALUE, "SHLVL"));
		if (shlvl == *((size_t *) env_handler(INITIAL_SHLVL_RETURN, NULL)))
			msg = ft_strdup("exit\n");
	}
	else
	{
		msg = ft_strjoin(
			ft_strjoin(
				"\033[1A\033[",
				ft_itoa(get_prompt_len()),
				e_false, e_true
			),
			"Cexit\n",
			e_true, e_false
		);
	}
	printf("%s", msg);
}

static size_t	get_prompt_len(void)
{
	size_t	len;
	char	*cwd;
	char	*last_cmd_exit_status;

	cwd = getcwd(NULL, PATH_MAX);
	if (0 == ft_strcmp(cwd, (char *) env_handler(BINDING_GET_VALUE, "HOME")))
		len = 1 + 1; // *~ plus space
	else
		len = get_cwd_len(cwd) + 1; // * counting /cwd plus ':'
	len += 8;
	last_cmd_exit_status = ft_itoa(g_env.last_executed_cmd_exit_status);
	len += ft_strlen(last_cmd_exit_status);
	free(last_cmd_exit_status);
	free(cwd);
	return (len + 1 + printer(GET_STDOUT_BYTE_SHIFT));
}

static size_t	get_cwd_len(char *cwd)
{
	size_t	offset;
	size_t	last_slash_pos;

	last_slash_pos = 0;
	offset = 0;
	while (cwd[offset])
	{
		if (cwd[offset] == '/')
			last_slash_pos = offset;
		offset++;
	}
	return (offset - last_slash_pos);
}
