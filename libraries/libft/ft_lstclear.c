/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:12:02 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/20 10:31:01 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!*lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		temp = temp -> next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	free(*lst);
}
