/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/13 16:09:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../types.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

/// user defined headers
# include "../types.h"

void		px_error_handler(int error, char *strerror,
				t_bool custom_message);
char		*ps_concatenate_args(char *old_args, char *new_arg,
				t_bool free_old, t_bool free_new);
char		*ft_return_path(char *cmd, char *const envp[]);
char		*ft_get_cmd_name(char *cmd);
size_t		px_strlcpy(char **dst, const char *src, size_t dstsize);
char		*px_strjoin(char const *s1, char const *s2);
void		*px_memcpy(void *dst, const void *src, size_t n);
int			px_strncmp(const char *s1, const char *s2, size_t n);
size_t		px_strlen(const char *str);
char		**px_split(char const *s, char c);
int			px_len_split(char **split);
char		*px_str_replace(char **str_old, char **str_new, t_boolean free_new);
t_bool	px_strcmp(char *s1, char *s2);
void		*px_splitclear(char **split);
void		px_putstr_fd(char *s, int fd);
char		*px_itoa(int n);
void		*px_malloc(size_t size);
void		px_free(void *ptr);
void		px_lstclear(t_cmd **lst, void (*del)(void *));

#endif