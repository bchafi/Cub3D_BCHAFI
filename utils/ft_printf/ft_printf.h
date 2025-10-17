/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:36 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/08 02:44:47 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putchr(int c);
int	ft_putnbr(int n);
int	ft_putstr(const char *str);
int	ft_hexadecimal(unsigned int num, char buffer);
int	ft_hexa_address(unsigned long num);

#endif
