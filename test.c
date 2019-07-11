#include "lem_in.h"

void	print_edge(t_edge *edge)
{
	if (edge->reverse)
		printf("|/%s/ %i/%i |", edge->to->name, edge->wgth, edge->reverse->wgth);
	else
		printf("|/%s/ %i/- |", edge->to->name, edge->wgth);
}

void	print_node(t_node *node)
{
	printf("/%s/ w=%i [ ", node->name, node->counter);
	t_list* tmp = node->links;
	while (tmp)
	{
		print_edge(((t_edge *)tmp->data));
		tmp = tmp->next;
	}
	printf("\n");
}
