/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:36:44 by nkunnath          #+#    #+#             */
/*   Updated: 2024/07/23 10:36:46 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_format(char c, va_list args, int *num_printed)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), num_printed);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), num_printed);
	else if (c == 'p')
	{
		ft_putstr("0x", num_printed);
		if (*num_printed == -1)
			return (*num_printed);
		ft_puthex((unsigned long long)va_arg(args, void *), 'x', num_printed);
	}
	else if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(args, int), num_printed);
	else if (c == '%')
		ft_putchar('%', num_printed);
	else if (c == 'u')
		ft_putunbr(va_arg(args, unsigned int), num_printed);
	else if (c == 'x' || c == 'X')
		ft_puthex(va_arg(args, unsigned int), c, num_printed);
	else
		ft_putchar(c, num_printed);
	return (*num_printed);
}

static int	end_list(va_list args)
{
	va_end(args);
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		num_printed;
	int		i;

	num_printed = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (check_format(format[++i], args, &num_printed) == -1)
				return (end_list(args));
		}
		else
		{
			if (write(1, &format[i], 1) == -1)
				return (end_list(args));
			num_printed += 1;
		}
		i += 1;
	}
	va_end(args);
	return (num_printed);
}
