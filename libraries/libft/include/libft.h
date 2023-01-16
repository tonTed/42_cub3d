/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:52:04 by tblanco           #+#    #+#             */
/*   Updated: 2023/01/14 13:11:01 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

# include "colors.h"

# define SPACE ' '

/* structures */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* checker functions */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_lower(int a, int b);
int		ft_bigger(int a, int b);
int		ft_ischarinstr(char c, char const *set);
int		ft_issetinstr(char const *s, char const *set);
bool	ft_issign(char c);
bool	ft_iswhitespace(char c);
bool	ft_isnumber(char *str);
bool	ft_isnumberstab(char **tab);
bool	ft_issorted(int *tab, size_t len);
bool	isnumberzero(char *str);
bool	ft_isduplicates(int *tab, int len);

/* char modifier functions */
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_swap(int *a, int *b);
void	ft_quicksort(int **tab, int start, int end);
void	ft_reversetab(int **tab, size_t len);

/* strings functions */
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
size_t	ft_strtablen(char **tab);
char	*ft_strjoin_free(char *begin, char *end);

/* convert functions */
int		ft_atoi(const char *str);
char	*ft_itoa(int nb);

/* memory functions */
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_freetabstr(char ***tab);
void	ft_freetabint(int **tab);

/* print functions */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_puttabstr_fd(char **tab, int fd);
void	ft_puttabint_fd(int *tab, size_t len, int fd);

/* list functions */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* error functions */
void	ft_errormess_fd(int fd, char *message);

#endif