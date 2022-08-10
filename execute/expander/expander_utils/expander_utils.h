/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:57 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/10 18:54:03 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

# include "../expander.h"

// * standard libraries //
# include <dirent.h>
# include <unistd.h>

char	*cwd_read(void);
char	**clean_results(char **results);
void	expansion_split(
				char *args,
				char **next_segment_ref,
				char **post_ref);
char	split_quoted_sequence(char *segment,
			char **pre_ref, char **post_ref);
char	*quote_as_string(char quote);

#endif