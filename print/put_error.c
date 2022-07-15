/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:05 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 16:42:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue)
{
	int	clone_stdout;

	clone_stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s", preamble);
	ft_printf(RED "%s" RESET, message);
	ft_printf("\n");
	if (epilogue)
		ft_printf("%s\n", epilogue);
	if (free_epilogue && epilogue)
		free(epilogue);
	dup2(clone_stdout, STDOUT_FILENO);
}
