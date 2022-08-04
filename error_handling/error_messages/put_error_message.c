/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:05 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 16:08:58 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

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
