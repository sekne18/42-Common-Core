/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:23:29 by fmol              #+#    #+#             */
/*   Updated: 2025/01/09 10:55:26 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16384//1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_lnode
{
	struct s_lnode	*next;
	char			*line;
	int				fd;
}	t_lnode;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_lnode	*lstfind_fd(t_lnode *start, int fd);
t_lnode	*lstadd_fd(t_lnode **start, int fd);
size_t	ft_strlen(const char *s);
void	reset_buffer(char *buffer);
void	append_buffer(char **s_line, char *buffer);
char	*ft_strjoin(char const *s1, char const *s2);
char	*create_line(char **s_line, int i);
char	*get_next_line(int fd);
int		has_char(char *buffer, size_t size, char c);
int		lstremove_fd(t_lnode **start, int fd);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

double	ft_atod(const char *nptr);
size_t	ft_strlen(const char *s);
size_t	ft_numlen(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void*src, size_t n);
void	*ft_memmove(void *dest, const void*src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int i, char *s));
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnstr_fd(const char *s, size_t n, int fd);
void	ft_putnendl_fd(const char *s, size_t n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_free_split(char **strs);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int i, char c));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsjoin(size_t size, char **strs, char *sep);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

#endif //LIBFT_H
