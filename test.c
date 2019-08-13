#include "lem_in.h"

#define QUE_SIZE 100 * sizeof(t_node*)

void	print_edge(t_edge *edge)
{
		ft_printf("|/%s{Red}%p{eof}->%s{Red}%p{eof}/ %i ", edge->from->wrap->name, edge->from,
				edge->to->wrap->name, edge->to, edge->wgth, edge->was_rev);
		if (edge->was_rev)
			ft_printf("{Red}(rev){eof} |");
		else
			ft_printf("{Blue}(not_rev){eof} |");
}

void	print_node(t_node *node)
{
	if ((t_edge *)node->links && (node->wrap == ((t_edge *)node->links->data)->to->wrap))
		ft_printf("{Yellow}");
	ft_printf("/%s/{Red}%p{eof} w=%i {eof}[ ", node->wrap->name, node, node->counter);
	t_list* tmp = node->links;
	while (tmp)
	{
		print_edge(((t_edge *)tmp->data));
		tmp = tmp->next;
	}
	ft_printf(" ]\n");
}
