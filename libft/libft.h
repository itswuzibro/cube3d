/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:49:21 by jde-sain          #+#    #+#             */
/*   Updated: 2025/09/19 18:51:37 by jde-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "get_next_line.h"
# include "ft_printf.h"
# include <ctype.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <bsd/string.h>
# include <unistd.h>

# define TRUE	1
# define FALSE	0

int					ft_str_isdigit(char *s);
char				**ft_addstr_to_tab(char *str, char **tab);
char				**ft_sort_strtab(char **tab);
char				**ft_removestr_tab(char *str, char **tab);
char				*ft_char_kill(char *str, char c, int opt);
int					ft_found_char(char *s, char c);
void				ft_print_tab(char **tab);
void				ft_free_tab(char **tab);
int					ft_dprintf(int fd, const char *str, ...);
void				ft_swap_char(char *a, char *b);
void				ft_swap_str(char **a, char **b);
int					ft_tablen(char **tab);
long long int		ft_atoll(char *nptr);
void				sprint(char *msg, char *s);
void				iprint(char *msg, int i);

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
size_t				ft_strlen(char const *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big,
						const char *little, size_t len);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strjoin(char *s1, char *s2, int option);
char				*ft_strtrim(char *s1, char const *set, int opt);
char				*ft_strcat(char *dst, char *src);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_swap(int	*a, int *b);
int					ft_toupper(int c);
int					ft_tolower(int c);

#endif
