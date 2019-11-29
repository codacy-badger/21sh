/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/11/25 20:53:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

/*
** Type of structs content, PTR points to the content, CPY copy the content.
*/
# define PTR	0
# define CPY	1

typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;
typedef unsigned long	t_uint64;

/*
** -----------------------------Struct buffer-----------------------------
*/

typedef struct			s_buff
{
	unsigned char		*bytes;
	size_t				size;
	size_t				i;
	void				(*flush_func)(struct s_buff *buff);
	int					fd;
}						t_buff;

t_buff					*ft_buff_new(size_t buff_size, int fd,
									void (*flush_func)(t_buff *buff));
void					ft_bufferize(t_buff *buff, const char *data,
															size_t data_size);
void					ft_bufferize_nbr(t_buff *buff, long nbr, t_uint32 base,
																	int prefix);
void					ft_buff_flush(t_buff *buff);
void					ft_buff_del(t_buff *buff);

/*
** -----------------------------Struct queue-----------------------------
*/

typedef struct			s_queue
{
	void				*content;
	size_t				content_size;
	struct s_queue		*next;
}						t_queue;

t_queue					*ft_queue_new(const void *content, size_t content_size);
void					ft_enqueue(t_queue **queue, t_queue *new);
void					ft_dequeue(t_queue **queue, void (*del)(void *));
void					ft_queue_del(t_queue **queue, void (*del)(void *));
int						ft_queue_isempty(t_queue **queue);

/*
** -----------------------------Struct stack-----------------------------
*/

typedef struct			s_stack
{
	void				*content;
	size_t				content_size;
	struct s_stack		*next;
}						t_stack;

t_stack					*ft_stack_new(const void *content, size_t content_size);
void					ft_push(t_stack **stack, t_stack *new);
void					ft_pop(t_stack **stack, void (*del)(void *));
void					ft_pop_back(t_stack **stack, void (*del)(void *));
void					ft_stack_del(t_stack **stack, void (*del)(void *));
int						ft_stack_count(t_stack **stack);
int						ft_stack_isempty(t_stack **stack);

/*
** -----------------------------Struct list-----------------------------
*/

/*
** Add pointer to last elem.
** void *get_by_value(t_list *list, void *value);
** No doubles ?
*/

typedef struct			s_list
{
	struct s_list_elem	*elems;
	bool				circular;
	int					count;
}						t_list;

typedef struct			s_list_elem
{
	void				*content;
	size_t				content_size;
	struct s_list_elem	*prev;
	struct s_list_elem	*next;
	int					index;
	char				type;
}						t_list_elem;

/*
** Low level
*/
t_list_elem				*ft_list_elem_new(const void *content,
													ssize_t content_size);
void					ft_list_elem_del(t_list_elem **elem,
												void (*del)(void *, size_t));
void					ft_list_iter(t_list *list, int start, int end,
													void (*f)(t_list_elem *));
void					ft_list_incr_index(t_list *list, int start);
void					ft_list_decr_index(t_list *list, int start);
bool					ft_list_add_front(t_list *list, t_list_elem *new);
bool					ft_list_add_back(t_list *list, t_list_elem *new);
void					ft_list_del_front(t_list *list,
												void (*del)(void *, size_t));
void					ft_list_del_back(t_list *list,
												void (*del)(void *, size_t));

/*
** High level
*/
t_list					*ft_list_new(int circular);
t_list_elem				*ft_list_get_first(t_list *list);
t_list_elem				*ft_list_get_last(t_list *list);
t_list_elem				*ft_list_get_at(t_list *list, int index);
void					*ft_list_get_value_at(t_list *list, int index);
bool					ft_list_insert_at(t_list *list, const void *value,
													int index, ssize_t size);
void					ft_list_del_at(t_list *list, int index,
												void (*del)(void *, size_t));
void					ft_list_del(t_list **list, void (*del)(void *, size_t));

/*
** -----------------------------Struct hashtable-----------------------------
*/

typedef struct			s_hentry
{
	char				*key;
	void				*value;
	struct s_hentry		**head;
	struct s_hentry		*prev;
	struct s_hentry		*next;
	char				type;
}						t_hentry;

typedef struct			s_htable
{
	t_hentry			**table;
	t_uint32			count;
	t_uint32			size;
}						t_htable;

t_htable				*ft_htnew(t_uint32 size);

/*
** Low level
*/
t_hentry				*ft_hentrynew_cpy(const char *key,
										const void *value, size_t size);
t_hentry				*ft_hentrynew_ptr(const char *key,
														const void *value);
void					ft_hentrydel(t_hentry **ahentry);
t_hentry				*ft_htget(t_htable *htable, const char *key);
t_uint32				ft_hkey(t_htable *htable, const char *key);

/*
** High level
*/
int						ft_htadd(t_htable *htable, const char *key,
											const void *value, ssize_t size);
void					*ft_htgetval(t_htable *htable, const char *key);
void					ft_htclr(t_htable *htable);
void					ft_htdel(t_htable **ahtable);
void					ft_htdelone(t_htable *htable, const char *key);

/*
** -------------------------Dynamic strings------------------------
*/

typedef struct			s_dstr
{
	int					len;
	char				*str;
	int					capacity;
}						t_dstr;

t_dstr					*ft_dstr_new(size_t size);
void					ft_dstr_insert(t_dstr **str, char c, int index);

/*
** -----------------------------Memory-----------------------------
*/

void					*ft_memalloc(size_t size);
void					*ft_memrealloc(void **m, size_t old_size,
														size_t new_size);
void					ft_bzero(void *m, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_memdel(void **m);
void					*ft_memset(void *m, char c, size_t len);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);

/*
** -----------------------------Strings-----------------------------
*/

char					*ft_strnew(size_t size);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
int						ft_strcmp(const char *s1, const char *s2);
char					ft_strequ(const char *s1, const char *s2);
char					*ft_strchr(const char *str, int c);
char					*ft_strtrim(char *str);
char					*ft_strtok(char *str, const char *sep);
int						ft_strbrkt(char *str, int len);
void					ft_strremove(char *str, size_t len);
void					ft_strinsert(char *str, char *insert, ssize_t len);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strsub(char const *s, unsigned int start,
																size_t len);
char					*ft_strjoin(const char *s1, const char *s2);

/*
** -----------------------------Array-----------------------------
*/

char					**ft_strarray_dup(char **array);
char					**ft_strarray_realloc(char **array, size_t new_size);
void					ft_strarray_del(char ***array);
char					**ft_htable_to_array(t_htable *htable);

/*
** -----------------------------Path-----------------------------
*/

char					*ft_path_addsuffix(const char *path, const char *suffix,
																char free_old);
char					*ft_path_getsuffix(const char *path, char alloc);

/*
** -----------------------------Char-----------------------------
*/

int						ft_isprint(int c);
int						ft_iswhitespace(int c);
int						ft_isctrl(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);

/*
** -----------------------------Length-----------------------------
*/

size_t					ft_strlen(const char *str);
size_t					ft_nbrlen(long n, t_uint32 base);
size_t					ft_strarray_len(char **array);

/*
** -----------------------------Math-----------------------------
*/

double					ft_power(double nb, double pwr);
char					ft_isprime(long n);
long					ft_nextprime(long n);
unsigned int			ft_next_power_of_two(unsigned int v);

/*
** -----------------------------Conv-----------------------------
*/

t_uint32				ft_base_isvalid(char *base);
long					ft_atoi(const char *str);
long					ft_atoi_base(const char *nbr, t_uint32 base);
char					*ft_itoa(long n);
char					*ft_itoa_base(long n, t_uint32 base);

#endif
