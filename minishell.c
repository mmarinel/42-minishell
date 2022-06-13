/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/13 14:50:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signature(void);

char	*shell_read(void);

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

// void	quit_controller(void)
// {
// 	char	c;

// 	while (read(STDIN_FILENO, &c, sizeof(char)))
// 		;
// 	kill(0, SIGUSR1);
// }

int main(void)
{
	char	*command;
	// pid_t	monitor = 1;

	while (1)
	{
		command = shell_read();
		// [result, fd] = shell_evaluate(command) ....return struct
		// shell_print(fd, result) .....use write(fd, ...)
		free(command);
	}
	return 0;
}

char	*shell_read(void)
{
	char	*command;

	print_signature();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	command = "";
	while (*command == '\0')
	{
		command = readline(MAGENTA "prompettino: " RESET);
		if (!command)
			exit(EXIT_SUCCESS);
	}
	printf("line read: %s\n", command);
	return (command);
}

void	print_signature(void)
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
	printf(GREEN "Courtesy of:\n\tmmarinel\n\taligabbos\n\n" RESET);
}
