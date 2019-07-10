#include "lem_in.h"

t_node *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7;

t_node	*create_node(char *name)
{
	t_node* node = ft_memalloc(sizeof(t_node));

	node->name = name;
	node->counter = -1;
	node->path = NULL;
	node->links = NULL;
	return (node);
}

void	bound_edge(t_node *from, t_node *to)
{
	t_edge* edge = ft_memalloc(sizeof(t_edge));
	t_edge* rev_edge = ft_memalloc(sizeof(t_edge));

	edge->wgth = -1;
	edge->from = from;
	edge->to = to;
	rev_edge->wgth = -1;
	rev_edge->from = to;
	rev_edge->to = from;

	t_list* new_e = ft_lstnew(edge, sizeof(t_edge));
	t_list* new_rev_e = ft_lstnew(rev_edge, sizeof(t_edge));

	ft_lstadd(&from->links, new_e);
	ft_lstadd(&to->links, new_rev_e);
	((t_edge *)new_e->data)->reverse = (t_edge *)new_rev_e->data;
	((t_edge *)new_rev_e->data)->reverse = (t_edge *)new_e->data;
}

#define EDGE ((t_edge *)child->data)

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
//	if (node->path)
//		ft_printf(" ] | path=%s\n", node->path->from->name);
//	else
//		printf(" ] | path=NULL\n");
}

void	print_gr()
{
	print_node(n0);
	print_node(n1);
	print_node(n2);
	print_node(n3);
	print_node(n4);
	print_node(n5);
	print_node(n6);
	print_node(n7);
	printf("\n--------------\n");
}

void	test1()
{
	n0 = create_node("0");
	n1 = create_node("1");
	n2 = create_node("2");
	n3 = create_node("3");
	n4 = create_node("4");
	n5 = create_node("5");
	n6 = create_node("6");
	n7 = create_node("7");

	bound_edge(n0, n4);
	bound_edge(n0, n6);
	bound_edge(n1, n3);
	bound_edge(n4, n3);
	bound_edge(n5, n2);
	bound_edge(n3, n5);
	bound_edge(n4, n2);
	bound_edge(n2, n1);
	bound_edge(n7, n6);
	bound_edge(n7, n2);
	bound_edge(n7, n4);
	bound_edge(n6, n5);
}

void my_test()
{
	test1();
	print_gr();
//	set_weights(n1);
//	print_gr();
	get_all_paths(n1, n0, 10);
}