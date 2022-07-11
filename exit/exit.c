/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:07:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/11 21:29:29 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	print_message(char *prompt, t_bool ctrl_d);

// * end of static declarations //


/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, char *prompt, t_bool ctrl_d)
{
	print_message(prompt, ctrl_d);
	ft_free(*ft_add_history(NULL)); // ! potevo anche fare ft_clear history senza copiare la stringa nella funzione chiamata ft_add_history
	rl_clear_history();
	sig_handling_set(SIG_AT_EXIT);
	free(prompt);
	exit(exit_status);
}

// void	exit_command_subshell(int exit_status, t_tree_node *parse_tree)
// {
// 	// TODO
// }
static void	print_message(char *prompt, t_bool ctrl_d)
{
	size_t	shlvl;
	char	*msg;
	size_t	prompt_len;

	if (prompt)
		;
	if (e_false == ctrl_d)
	{
		shlvl = atoi(env_handler(BINDING_GET_VALUE, "SHLVL"));
		if (shlvl == *((size_t *) env_handler(INITIAL_SHLVL_RETURN, NULL)))
			msg = ft_strdup("exit\n");
	}
	else
	{
		int	i;
		i = 0;
		prompt_len = 0;
		while (prompt[i])
		{
			if (prompt[i] == ':')
				prompt_len = i + 1;
			i++;
		}
		msg = ft_strjoin(
			ft_strjoin(
				"\033[1A\033[",
				ft_itoa(21 - 9 + ft_atoi(env_handler(BINDING_GET_VALUE, "PWD"))),
				e_false, e_true
			),
			"Cexit\n",
			e_true, e_false
		);
	}
	printf("%s", msg);
	printf("%zu\n", ft_strlen(prompt));
}
