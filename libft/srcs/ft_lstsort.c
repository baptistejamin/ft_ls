/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:13:38 by bjamin            #+#    #+#             */
/*   Updated: 2015/12/04 11:19:13 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void __back_split(t_list *src, t_list **head, t_list **back)
{
  t_list *fast;
  t_list *slow;

  if (src==NULL || src->next==NULL)
  {
    *head = src;
    *back = NULL;
  }
  else
  {
    slow = src;
    fast = src->next;
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
    *head = src;
    *back = slow->next;
    slow->next = NULL;
  }
}

t_list *__sorted_merge(t_list * a, t_list * b, 
	int (*cmp)(void *_a, void *_b), void *(*get_data)(t_list *e))
{
  t_list * result = NULL;

  if (a == NULL)
     return(b);
  else if (b == NULL)
     return(a);
  if (cmp(get_data(a), get_data(b)))
  {
     result = a;
     result->next = __sorted_merge(a->next, b, cmp, get_data);
  }
  else
  {
     result = b;
     result->next = __sorted_merge(a, b->next, cmp, get_data);
  }
  return(result);
}
 

void ft_lstsort(t_list** list, 
	int (*cmp)(void *_a, void *_b), void *(*get_data)(t_list *e))
{
	t_list *head;
  t_list* a;
  t_list* b;

  head = *list;
  if ((head == NULL) || (head->next == NULL))
    return ;
  __back_split(head, &a, &b); 
  ft_lstsort(&a, cmp, get_data);
  ft_lstsort(&b, cmp, get_data);
  *list = __sorted_merge(a, b, cmp, get_data);
}
