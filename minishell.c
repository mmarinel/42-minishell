/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 15:51:43 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(char *const envp[]);
static void	print_signature(void);
static void	unlink_here_docs(void);
static void	set_pid_variable(void);
//* end of static declarations

int	main(int argc, char const *argv[], char *const envp[])
{
	t_tree_node	*parse_tree;

	if (argc != 1)
	{
		put_error(ARGS_ERROR, EXIT_FAILURE, (void *)(argv[1]));
		exit(EXIT_FAILURE);
	}
	set_env(envp);
	sig_handling_set(SIG_INITIAL);
	print_signature();
	while (e_true)
	{
		parse_tree = shell_read();
		execute(parse_tree);
		{
			tokenizer_free();
			free_tree(&parse_tree);
			unlink_here_docs();
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * ```
 * this function sets the current environment,
 * increments SHLVL variable,
 * duplicates 'real' stdout (as long as it wasn't redirected through
 * the outside -non minishell-shell)
 * if this is the first minishell call
 * and sets the $? env variable.
 * ```
 * 
 */
static void	set_env(char *const envp[])
{
	size_t	cur_shlvl;
	char	*new_shlvl_str;

	env_handler(ENV_INITIALIZE, (char **)envp);
	set_pid_variable();
	printf("my pid is %d\n", g_env.pid);
	{
		cur_shlvl = ft_atoi(env_handler(BINDING_GET_VALUE, "SHLVL"));
		new_shlvl_str = ft_itoa(cur_shlvl + 1);
		env_handler(BINDING_UPDATE,
			get_new_binding("SHLVL", new_shlvl_str, e_false));
		free(new_shlvl_str);
	}
	if (NULL == env_handler(BINDING_GET_VALUE, "minishell_first_call_set"))
	{
		printf("in stdout_clone set\n");
		env_handler(BINDING_UPDATE,
			get_new_binding("minishell_first_call_set", "1", e_false));
		g_env.stdout_clone = dup(STDOUT_FILENO);
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

/**
 * @brief this function sets the $$ env variable
 * 
 */
static void	set_pid_variable(void)
{
	pid_t	pid;
	int		pid_val_channel[2];
	int		shell_exit_value;

	pipe(pid_val_channel);
	pid = fork();
	if (pid == 0)
	{
		close(pid_val_channel[1]);
		read(pid_val_channel[0], &g_env.pid, sizeof(pid_t));
		close(pid_val_channel[0]);
	}
	else
	{
		signal(SIGINT, sig_ign);
		signal(SIGQUIT, sig_ign);
		close(pid_val_channel[0]);
		write(pid_val_channel[1], &pid, sizeof(pid_t));
		close(pid_val_channel[1]);
		env_handler(ENV_CLEAN, NULL);
		waitpid(pid, &shell_exit_value, 0);
		exit(WEXITSTATUS(shell_exit_value));
	}
}

/**
 * @brief this function removes here docs buffer files from the file system
 * 
 */
static void	unlink_here_docs(void)
{
	t_bool			repeat;
	char			*next_here_doc;
	size_t			progressive_nbr;
	char			*prefix;

	prefix = ".here_doc-";
	progressive_nbr = 0;
	repeat = e_true;
	while (repeat)
	{
		next_here_doc = ft_strjoin(prefix, ft_itoa(progressive_nbr),
				e_false, e_true);
		if (access(next_here_doc, R_OK | W_OK) != 0)
			repeat = e_false;
		else
			unlink(next_here_doc);
		free(next_here_doc);
		progressive_nbr++;
	}
}

/**
 * @brief this function prints the project signature to the 'real stdout'
 * ('real' as long we didn't redirect it during first execution through
 * another shell such as bash, zsh, sh, etc.)
 * That's why we dup STDOUT_FILENO inside the body.
 */
static void	print_signature(void)
{
	int		cur_stdout_backup;

	{
		cur_stdout_backup = dup(STDOUT_FILENO);
		dup2(g_env.stdout_clone, STDOUT_FILENO);
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
		dup2(cur_stdout_backup, STDOUT_FILENO);
		close(cur_stdout_backup);
	}
}
