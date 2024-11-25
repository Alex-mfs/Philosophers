/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 19:04:48 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
//ft_printf
# define CONVERSION "cspdiuxX%"
# define FLAGS "-0# +"
# define DECIMAL "0123456789"
# define HEXA_LOW "0123456789abcdef"
# define HEXA_UPP "0123456789ABCDEF"
//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif
# define MAXFD 2000

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}			t_list;

// Memory
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_matrix(char **tab);
void	ft_free_intmatrix(int **mat, size_t size);

// Checks
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);
bool	ft_isdelim(int c);
int		ft_smaller_int(int n1, int n2);

// Error Handling
int		ft_error_msg(char *str);
void	ft_error_exit(char *str);

// Conversions
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);

// Strings - Info
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strchr_pos(const char *str, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strnstr_pos(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	ft_str_cmp(const char *s1, const char *s2);
bool	ft_rptcheck_str(char **str);
// Strings - Simple Operations
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strbuild(char *s1, const char *s2);
char	*ft_substr(const char *str, unsigned int start, size_t len);
// Strings - Complex Operations
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_str_repl_chr(char *str, char old, char new, size_t times);
char	*ft_str_repl_seg(const char *str, char *old, char *new);
char	**ft_matrix_dup(char **src);
char	**ft_matrix_add_line(char **src, char *newline);
void	ft_striteri(char *str, void (*f)(unsigned int, char *));
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
char	**ft_split(const char *s, char c);
char	*get_next_line(int fd);

// Arrays
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Printing
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
int		ft_putnbr_fd(long n, int fd);
int		ft_putnbr_ubase_fd(unsigned int nbr, char *base, int fd);
int		ft_putnbr_lbase_fd(unsigned long nbr, char *base, int fd);
int		ft_printf(const char *string, ...);

// Structures
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	flood_fill(char **tab, t_point size, t_point begin);

#endif
