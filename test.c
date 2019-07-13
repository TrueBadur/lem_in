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

void	create_edge(t_node *from, t_node *to)
{
	t_edge *ed = ft_memalloc(sizeof(t_edge));

	ed->was_rev = 0;
	ed->wgth = -1;
	ed->from = from;
	ed->to = to;
	ft_lstadd(&from->links, ft_lstnew(ed, sizeof(t_edge)));
	free(ed);
}

void	bound_nodes(t_wnode *from, t_wnode *to)
{
	create_edge(&from->out, &to->in);
	create_edge(&to->out, &from->in);
//	print_node(&from->out);
//	print_node(&to->out);
}

t_wnode	*create_wnode(char *name)
{
	t_wnode *wn = ft_memalloc(sizeof(t_wnode));

	wn->name = name;
	wn->in.wrap = wn;
	wn->in.counter = -1;
	wn->in.path = NULL;
	wn->out.wrap = wn;
	wn->out.counter = -1;
	wn->out.path = NULL;
	wn->out.links = NULL;
	wn->in.links = NULL;

	t_edge *ed = ft_memalloc(sizeof(t_edge));
	ed->was_rev = 0;
	ed->wgth = -1;
	ed->from = &wn->in;
	ed->to = &wn->out;
	ft_lstadd(&wn->in.links, ft_lstnew(ed, sizeof(t_edge)));
	free(ed);

//	print_node(&wn->in);
//	print_node(&wn->out);
	return wn;
}

void	test_1(t_mngr *mngr)
{
	t_wnode *n2, *n3, *n4, *n5, *n6, *n7;

	mngr->ant_num = 10;
	mngr->start = &create_wnode("1")->out;
	mngr->end = &create_wnode("0")->in;
	n3 = create_wnode("3");
	n2 = create_wnode("2");
	n4 = create_wnode("4");
	n5 = create_wnode("5");
	n6 = create_wnode("6");
	n7 = create_wnode("7");
	bound_nodes(mngr->start->wrap, n2);
	bound_nodes(mngr->start->wrap, n3);
	bound_nodes(mngr->end->wrap, n4);
	bound_nodes(mngr->end->wrap, n6);
	bound_nodes(n4, n3);
	bound_nodes(n5, n2);
	bound_nodes(n3, n5);
	bound_nodes(n4, n2);
	bound_nodes(n7, n6);
	bound_nodes(n7, n2);
	bound_nodes(n4, n7);
	bound_nodes(n5, n6);
}

void	test_2(t_mngr *mngr)
{
	t_wnode *b, *c, *e, *f, *g, *h;

	mngr->ant_num = 10;
	mngr->start = &create_wnode("a")->out;
	mngr->end = &create_wnode("d")->in;
	b = create_wnode("b");
	c = create_wnode("c");
	e = create_wnode("e");
	f = create_wnode("f");
	g = create_wnode("g");
	h = create_wnode("h");
	bound_nodes(mngr->start->wrap, b);
	bound_nodes(mngr->start->wrap, e);
	bound_nodes(mngr->end->wrap, c);
	bound_nodes(mngr->end->wrap, g);
	bound_nodes(e, c);
	bound_nodes(b, f);
	bound_nodes(b, c);
	bound_nodes(g, h);
	bound_nodes(h, f);
}

void	test_3(t_mngr *mngr)
{
	t_wnode *b, *e, *f;

	mngr->ant_num = 10;
	mngr->start = &create_wnode("a")->out;
	mngr->end = &create_wnode("c")->in;
	b = create_wnode("b");
	e = create_wnode("e");
	f = create_wnode("f");
	bound_nodes(mngr->start->wrap, b);
	bound_nodes(mngr->start->wrap, e);
	bound_nodes(mngr->end->wrap, b);
	bound_nodes(mngr->end->wrap, f);
	bound_nodes(e, b);
	bound_nodes(b, f);
}

void	test(t_mngr *mngr)
{
	test_2(mngr);
}
