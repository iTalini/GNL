/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:49:03 by akurilen          #+#    #+#             */
/*   Updated: 2018/01/03 15:49:08 by akurilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstshift(t_list **alst)
{
	t_list *new_first;

	if (alst != NULL && *alst != NULL)
	{
		new_first = (*alst)->next;
		free(*alst);
		*alst = new_first;
	}
}
