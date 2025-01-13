/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:34:38 by nkunnath          #+#    #+#             */
/*   Updated: 2024/07/24 11:34:39 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c, int *num_printed)
{
	int	x;

	x = write(1, &c, 1);
	if (x == -1)
	{
		*num_printed = -1;
		return ;
	}
	*num_printed += 1;
}
