/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarget <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 15:42:30 by dmarget           #+#    #+#             */
/*   Updated: 2020/12/11 17:27:47 by dmarget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_enti
{
	va_list				ap;
	char				*print;
	int					minus;
	int					zero;
	int					width;
	int					width_len;
	int					precision;
	int					precision_len;
	int					ste;
	int					type;
	char				*s;
	int					str_len;
	int					i;
	int					count;
	int					len;
	int					sign;
	unsigned long		six;
}				t_enti;

int				ft_printf(char *format, ...);
void			ft_init(t_enti *enti);
void			ft_reinit(t_enti *enti);
void			ft_parser(t_enti *enti);
void			ft_putchr(char c, t_enti *enti);
size_t			ft_strlen(const char *str);
void			ft_putnbr(int n, t_enti *enti);
void			ft_putnbr_u(unsigned int n, t_enti *enti);
void			ft_putnbr_hex(unsigned int n, unsigned int base,
				t_enti *enti, char c);
void			ft_putnbr_hex_p(unsigned long n, unsigned int base,
				t_enti *enti);
void			ft_putstr(t_enti *enti);
int				ft_atoi(const char *s, t_enti *enti);
void			valid(t_enti *enti);
void			print_int(t_enti *enti);
void			print_chr(t_enti *enti);
void			print_str(t_enti *enti);
void			print_p(t_enti *enti);
void			print_u(t_enti *enti);
void			print_hex(t_enti *enti);
void			print_cap_hex(t_enti *enti);
void			print_per(t_enti *enti);

#endif
