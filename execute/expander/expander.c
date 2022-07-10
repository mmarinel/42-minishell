/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_new copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/09 18:53:50 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

# include <fcntl.h>

char	*expand(char *args)
{
	// int fd = open("test", O_RDWR | O_CREAT | O_TRUNC);
	// write(fd, args, sizeof(args));//(YELLOW "expand with arg: %s" RESET, args);
	if (!args || !(*args))
		return (args);
	args = expand_dollar_case(args);
	args = expand_star_case(args);
	return (args);
}
