/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/05 21:51:40 by ferfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <curses.h>
# include <termios.h>
# include <term.h>

enum	e_caps
{
		C_UP,
		C_DO,
		C_LE,
		C_ND,
		C_HO,
		C_CE,
		C_CD,
		C_DC,
		C_SC,
		C_RC,
		C_CR,
		C_SF,
		C_SR,
		C_CM,
		C_CL,
		C_BL,
		CAPS_SIZE
};

typedef struct		s_term
{
	struct winsize	win;
	struct termios	oldterm;
	struct termios	newterm;
	char			*caps[CAPS_SIZE];
	size_t			size;
	size_t			cpos;
}					t_term;

int					init_term(struct s_term *term);

int					getwinsize(t_term *term);
int					getcpos(t_term *term);
void				setcpos(t_term *term, size_t value);
void				incrcpos(t_term *term, size_t value);
void				decrcpos(t_term *term, size_t value);
void				movcleft(t_term *term);
void				movcright(t_term *term);
void				movcto(t_term *term, size_t pos);
void				movcnl(t_term *term);
void				clearfromc(t_term *term);
int					printstr(t_term *term, char *str);
int					ft_putc(int c);

/*
size_t				display_char(t_term *term, char *c);
size_t				display_str(t_term *term, char *s);
size_t				display_nl(t_term *term);
void				clear_fromc(t_term *term);
int					movcdown(t_term *term);
int					movcup(t_term *term);
int					movcleft(t_term *term);
int					movcright(t_term *term);
void				movchx(t_term *term);
void				movchy(t_term *term);
void				movch(t_term *term);
void				movcex(t_term *term);
void				movcey(t_term *term);
void				movce(t_term *term);

*/
#endif 
