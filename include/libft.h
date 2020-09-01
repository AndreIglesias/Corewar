/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:28:56 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/30 12:34:52 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

# define BUFF_SIZE 6
# define BOLD "\e[1m"
# define DIM "\e[2m"
# define ITALIC "\e[3m"
# define UNDERL "\e[4m"
# define BLINK "\e[5m"
# define REVER "\e[7m"
# define INVIS "\e[8m"
# define RED "\e[38;2;255;0;0m"
# define GREEN "\e[92m"
# define CYAN "\e[96m"
# define BLUE "\e[34m"
# define YELLOW "\e[33m"
# define ERROR "\e[38;2;255;0;0m\e[1mERROR\e[0m\e[38;2;255;0;0m"
# define BLACKB "\e[40m"
# define GRAY "\e[90m"
# define E0M "\e[0m"

typedef struct		s_list
{
	void			*obj;
	size_t			dim;
	struct s_list	*next;
}					t_list;

typedef struct		s_listi
{
	int				data;
	struct s_listi	*next;
}					t_listi;

int					ft_mod(int a, int b);
int					ft_isint(char *str);
int					ft_printf(const char *format, ...);
int					ft_printf_fd(const int fd, const char *format, ...);
int					ft_scmp(const char *s, const char *s1, const char *s2);
int					ft_puterr(char const *s, int ex);
int					exceeds_int(char *nb);
int					free_split(char **strs);
intmax_t			ft_abs(intmax_t x);
void				ft_freesv(char **m, char *end);
char				**ft_vstrdup(char **m, char *end);
char				*ft_cpyxchr(char *str, char *dst, char c, int n);
char				*ft_fillstr(char c, int q);
char				*ft_chgchr(char *s, char old, char nw);
double				ft_sqrt(int n);
int					ft_countchr(const char *s, int c);
int					get_next_line(int const fd, char **line);
int					get_next_line2(const int fd, char **line, char **pitcher);
char				*ft_strndup(const char *s, size_t n);
char				*ft_fstrjoin(char *s1, char *s2);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *restrict dst, const void *restrict src,
								size_t n);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
								int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,
								size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *restrict s1, const char *restrict s2,
								size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int n);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
int					ft_repet(char c, int i);
int					ft_putchar(char c);
int					ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
int					ft_putnbr_max(uintmax_t x, int fd);
int					ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew2(void *content, size_t content_size);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_atoi_protected(const char *str);
int					ft_do_op(int ac, char **av);
int					ft_fprime(int nb);
void				ft_pgcd(int a, int b);
unsigned char		ft_swap_bits(unsigned char octet);
int					ft_ulstr(char *str);
t_listi				*ft_sort_list(t_listi *lst, int (*cmp)(int, int));
char				*ft_strrev(char *str, int size);
char				*ft_itoa_base(int value, int base);

#endif
