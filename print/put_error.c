/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:05 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 18:38:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_error(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue)
{
	int	clone_stdout;

	clone_stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s", preamble);
	printf(RED "%s" RESET, message);
	if (epilogue)
		printf("%s", epilogue);
	printf("\n");
	if (free_epilogue)
		free(epilogue);
	dup2(clone_stdout, STDOUT_FILENO);
}
