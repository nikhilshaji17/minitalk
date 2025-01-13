/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:37:19 by nkunnath          #+#    #+#             */
/*   Updated: 2024/12/19 18:37:21 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define MAX_LIMIT 4194304
# define MIN_LIMIT -4194304

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h> 
# include <signal.h> 
# include <stdlib.h> 
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>

enum
{
	READY,
	BUSY,
};

void	sigac_wrapper(int signo, void *handler, bool use_siginfo);
void	kill_wrapper(pid_t pid, int signo);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_putchar(char c, int *num_printed);
void	ft_putstr(char *s, int *num_printed);
void	ft_putnbr(int n, int *num_printed);
void	ft_putunbr(unsigned int n, int *num_printed);
void	ft_puthex(unsigned long long n, char c, int *num_printed);
int		ft_printf(const char *format, ...);

#endif
