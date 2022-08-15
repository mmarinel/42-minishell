/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:43:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

//* std libs
# include <stdlib.h>
# include <stdio.h>

//* useful macros
# include <limits.h>

//* read, write, file handling ...
# include <unistd.h>
# include <fcntl.h>

//* user defined modules //
# include "simple_printf/ft_printf_module.h"
# include "../colors.h"

//* user defined types
# include "../types.h"

//* includes end //

//* string utils

//* common

char			*ft_strjoin(char *pre, char *post,
					t_bool free_pre, t_bool free_post);
char			*ft_strdup(char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_str_replace(char **str, char *new);
size_t			ft_strlcpy(char **dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
char			*ft_strcpy(char *buf, char *src, int copy_len);
t_bool			str_not_empty(char *str);

//*  string strip

char			*string_strip(char *str, char to_strip, t_bool free_input);
char			*str_strip_spaces(char *str);

//*substr, word, etc.

char			*ft_substr(char *str, char delimiter);
char			*take_substr(char *str, char *substr);
char			*take_next_word(char *str);

// * itoa

char			*ft_itoa(int nbr);

//* special chars, occurrences, etc.

size_t			skip_consecutive_chars(char *string, size_t offset,
					char to_skip, int direction);
size_t			skip_past_char(char *str, size_t offset,
					char to_skip, int direction);
t_bool			ft_isspace(char c);
t_bool			ft_is_digit_string(char *str);
t_bool			ft_is_alpha_string(char *str);
t_bool			ft_is_alphanumeric_string(char *str);
t_bool			char_is_alpha(char c);
t_bool			char_is_digit(char c);
char			take_starting_quote(char *str);
int				str_number_occurrences(char *str, char c);

//* split

char			**ft_split(char const *string, char delimiter);
void			*ft_splitclear(char **split);
char			*split_merge(char	**split, char *const sep,
					t_bool free_split);
size_t			split_len(char **split);

//* math utils

int				ft_atoi(const char *str);
unsigned int	ft_pow(unsigned int m, unsigned int e);
int				range_spill(int point, int right_edge,
					int left_spill_val, int right_spill_val);
void			flip(t_bool *value);

//* memory utils //

void			*ft_malloc(size_t size);
void			ft_free(void *ptr);

// * shell utils

size_t			bash_next_word_len(char *command_line, size_t offset);
size_t			bash_next_string_len(char *str, size_t offset);
t_bool			is_env_var_name(char *str);
t_bool			bash_word_is_empty(char *command);
t_bool			command_is_empty(char *command);
void			set_error(t_status *status);
t_bool			ft_pending_pipe(char *command);
t_bool			ft_pending_logical_op(char *command);
t_bool			bash_control_character(char c);
t_bool			ft_is_quote(char c);
t_bool			bash_cmd_separator(char c);
t_bool			redirect_char(char c);
void			clone_pipe(int target[2], int clone[2]);
void			close_pipe(int pipe_[]);
int				ft_open(char *file_name,
					unsigned long long flags, int mode,
					t_bool free_file_name);
int				ft_unlink(char *file_name, t_bool free_file_name);

#endif