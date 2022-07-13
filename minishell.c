/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 11:16:16 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(char *const envp[]);
static void	print_signature(void);
static void	unlink_here_docs(void);

int	main(int argc, char const *argv[], char *const envp[])
{
	t_tree_node	*parse_tree;

	if (argc != 1)
	{
		printf(RED "no arguments allowed\n" RESET
		CYAN "found argument: " RESET
		YELLOW"%s\n" RESET,
		*(argv + 1));
		exit(EXIT_FAILURE);
	}
	set_env(envp);
	sig_handling_set(SIG_INITIAL);
	print_signature();
	while (e_true)
	{
		parse_tree = shell_read();
		execute(parse_tree);
		tokenizer_free();
		free_tree(&parse_tree);
		unlink_here_docs();
	}
	// clear_history();
	return (EXIT_SUCCESS);
}

/**
 * @brief this function saves the current env after incrementing variable SHLVL
 * 
 * @param envp 
 */
static void	set_env(char *const envp[])
{
	size_t	cur_shlvl;

	env_handler(ENV_INITIALIZE, (char **)envp);
	cur_shlvl = ft_atoi(env_handler(BINDING_GET_VALUE, "SHLVL"));
	env_handler(BINDING_UPDATE,
		get_new_binding("SHLVL", ft_itoa(cur_shlvl + 1), e_false));
	env_handler(SET_INITIAL_SHLVL, NULL);
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	// env_handler(_PRINT_ENV_, NULL);
}

/**
 * @brief this function removes here docs buffer files from the file system
 * 
 */
static void	unlink_here_docs(void)
{
	char	*prefix;
	size_t	progressive_nbr;
	char	*next_here_doc;
	t_bool	repeat;

	prefix = ".here_doc-";
	progressive_nbr = 0;
	repeat = e_true;
	while (repeat)
	{
		next_here_doc = ft_strjoin(prefix, ft_itoa(progressive_nbr),
							e_false, e_true);
		if (access(next_here_doc, R_OK | W_OK) == 0)
			unlink(next_here_doc);
		else
			repeat = e_false;
		free(next_here_doc);
	}
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
	printf(CYAN "Courtesy of:\n\tmmarinel\n\taligabbos\n\n" RESET);
}
