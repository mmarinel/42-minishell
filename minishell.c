/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/30 11:03:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_signals(void);
static void	print_signature(void);

/**
 * @brief this function sets signals handlers
 * and disable echoing of special character ctr+c (^C)
 * 
 */
static void	set_signals(void)
{
	struct termios	tty_attrs;

	tcgetattr(STDIN_FILENO, &tty_attrs);
	tty_attrs.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char const *argv[], char *const envp[])
{
	char			*command;

	if (argc != 1)
		return (EXIT_SUCCESS);
	// g_shell_env = (t_shell_env *) malloc(sizeof(t_shell_env));
	g_env.last_executed_cmd_status = EXIT_SUCCESS;
	g_env.env = NULL;
	g_env.export = NULL;
	copy_env(&(g_env.env), (char **)envp, e_false);
	copy_env(&(g_env.export), (char **)envp, e_true);
	set_signals();
	print_signature();
	while (e_true)
	{
		command = shell_read(envp);
		// [result, fd] = shell_evaluate(command) ....return struct
		// shell_print(fd, result) .....use write(fd, ...)
		ft_free(command);
		// * unlink(".here_doc"); DEBUG: COMMENTED BECAUSE WE MAY NEED TO SEE WHAT'S INSIDE OF THE FILE
	}
	clear_history();
	return (EXIT_SUCCESS);
	if (argv)
	{}
}

static void	print_signature(void)
{
	printf(RED "\
888b     d888 d8b          d8b          888               888 888\n\
8888b   d8888 Y8P          Y8P          888               888 888\n\
88888b.d88888                           888               888 888\n\
888Y88888P888 888 88888b.  888 .d8888b  88888b. .d88b.    888 888\n\
888 Y888P 888 888 888 88b  888 88K      888 88b d8P  Y8b  888 888\n\
888  Y8P  888 888 888  888 888 Y8888b.  888  888 8888888  888 888\n\
888       888 888 888  888 888      X88 888  888 Y8b.     888 888\n\
888       888 888 888  888 888  88888P  888  888  Y8888   888 888\n\n" RESET);
	printf(RED "As Beautiful as a Shell 😏\n\n" RESET);
	printf(GREEN "Courtesy of:\n\tmmarinel\n\taligabbos\n\n" RESET);
}
