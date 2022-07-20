/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:05 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 11:18:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_error_message(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue)
{
	ft_printf("%s", preamble);
	ft_printf(RED "%s" RESET, message);
	ft_printf("\n");
	if (epilogue)
		ft_printf("%s\n", epilogue);
	if (free_epilogue && epilogue)
		free(epilogue);
}
