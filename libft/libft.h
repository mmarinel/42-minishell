/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:24:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/16 16:02:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

//* user defined modules //
# include "simple_printf/ft_printf_module.h"

# ifndef T_BOOL_H
#  define T_BOOL_H
typedef enum e_bool
{
	e_true = 1,
	e_false = 0
}	t_bool;
# endif

//* string utils

	//* common

char			*ft_strjoin(char *pre, char *post, t_bool free_pre, t_bool free_post);
char			*ft_strdup(char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_str_replace(char **str, char *new);
size_t			ft_strlcpy(char **dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
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
t_bool			char_is_alpha(char c);
t_bool			char_is_digit(char c);
char			take_starting_quote(char *str);
t_bool			ft_quote_occurrence_balanced(char *str);
int				str_number_occurrences(char *str, char c);


//* split

char			**ft_split(char const *string, char delimiter);
void			*ft_splitclear(char **split);
char			*split_merge(char	**split, char *const sep, t_bool free_split);


//* math utils

int				ft_atoi(const char *str);
unsigned int	ft_pow(unsigned int m, unsigned int e);
int				range_spill(int point, int right_edge,
					int left_spill_val, int right_spill_val);
void			flip(t_bool *value);

//* memory utils //

void			*ft_malloc(size_t size);
void			ft_free(void *ptr);

#endif