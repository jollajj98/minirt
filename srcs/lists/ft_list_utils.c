#include <stdlib.h>
#include "ft_list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = 0;
	return (list);
}

unsigned int	ft_lstsize(t_list *first)
{
	int		size;
	t_list	*current;

	size = 0;
	current = first;
	while (current)
	{
		current = current->next;
		size++;
	}
	return (size);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current)
	{
		while (current->next)
			current = current->next;
	}
	return (current);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	while (current)
	{
		if (del != 0)
			del(current->content);
		temp = current->next;
		free (current);
		current = temp;
	}
}
