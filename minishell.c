/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/14 17:23:58 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*shell_read( char *const envp[]);
static void	print_signature(void);

/**
 * @brief handler for all
 * 
 * @param signum 
 */
void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		exit(EXIT_FAILURE);
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char const *argv[], char *const envp[])
{
	char	*command;

	if (argc != 1)
		return (EXIT_SUCCESS);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	print_signature();
	while (e_true)
	{
		command = shell_read(envp);
		// [result, fd] = shell_evaluate(command) ....return struct
		// shell_print(fd, result) .....use write(fd, ...)
		free(command);
	}
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
