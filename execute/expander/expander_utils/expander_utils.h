/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:57 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/09 19:46:12 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

# include "../expander.h"

// * standard libraries //
# include <dirent.h>

char	*cwd_read(void);
char	**clean_results(char **results);
void	expansion_split(t_special_char special_char,
				char *args,
				char **next_segment_ref,
				char **post_ref);

#endif