/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:28:27 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/03 22:13:28 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new_lst;
	t_list	*memo;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		memo = ft_lstnew((*f)(lst->content));
		if (memo == NULL)
		{
			ft_lstclear(&new_lst);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, memo);
		lst = lst->next;
	}
	return (new_lst);
}
