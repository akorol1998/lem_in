/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:10:11 by akorol            #+#    #+#             */
/*   Updated: 2019/06/06 11:10:23 by akorol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int			launch_algorithm(t_table *tbl)
{
	t_node	*curr;
	int		idx;
	int		f;
	int		i;

	curr = tbl->nodes;
	f = 1;
	ft_putstr("node before ");	
	while ((idx = set_levels(tbl)) && f)
	{
		if (idx == -1)
		{
			printf("There are no available paths to an end Not enough info, can't reach end\n"); // One ending
			return (0);
		}
		f = extract_path(tbl, idx);
		i = -1;
		while (tbl->q[++i])
			tbl->q[i] = NULL;
	}
	if (!idx)
	{
		printf("Start has no linkage or all available paths are taken\n");
		return (0);
	}
	else
		printf("good\n");
	return (1);
}

void		making_path(t_table *tbl, int idx, int	j, int size)
{
	t_node	*node;

	node = tbl->q[idx];
	tbl->path[j][size] = node; // End node, don't mark as visited
	while (ft_strcmp(node->name, tbl->start->name))
	{
		node = node->prev;
		node->visited = 1;
		ft_putstr(" middle node");
		ft_putstr(node->name);
		ft_putstr("\n");
		size--;
		tbl->path[j][size] = node;
	}
	if (!ft_strcmp(node->name, tbl->start->name))
		node->visited = 0;
	ft_putnbr(tbl->end->visited);
	ft_putstr("\n");
}

int			extract_path(t_table *tbl, int idx)
{
	int		i;
	int		j;
	int 	size;

	i = -1;
	while (tbl->q[++i])
		;
	j = -1;
	while (tbl->path[++j])
		;
	if (!tbl->q[idx])
		return (-1);
	size = count_nodes(tbl, idx);
	tbl->path[j] = (t_node**)malloc(sizeof(t_node*) * size + 1);
	tbl->path[j][size] = NULL;
	making_path(tbl, idx, j, size - 1);
	if (j + 1 == tbl->ants)
		return (0);
	return (1);
}

void		add_to_queue(t_table *tbl, t_node *cur)
{
	t_pipe	*pip;
	int		i;
	int		flag;
	int		idx;

	idx = -1;
	pip = cur->branch;
	while (tbl->q[++idx])
		;
	pip = cur->branch;
	while (pip)
	{
		i = -1;
		flag = 1;
		while (tbl->q[++i])
		{
			if (pip->node->visited || !ft_strcmp(tbl->q[i]->name, pip->node->name))
				flag = 0;
		}
		if (flag)
		{
			tbl->q[idx] = pip->node;
			pip->node->prev = cur;
			idx++;
		}
		pip = pip->next;
	}
}

int			set_levels(t_table *tbl)
{
	t_node	*cur;
	int		idx;
	int		flag;
	t_pipe	*pip;

	idx = 0;
	flag = 0;
	cur = tbl->nodes;
	pip = cur->branch;
	// if (!ft_strcmp(cur->name, "start"))
	// 		printf("\nyes\n");
	// if (cur->branch)
	// 	printf("\nyes\n");
	while (pip)
	{
		if (!ft_strcmp(pip->node->name, "701"))
			printf("\nyes\n");
		if (!pip->node->visited)
			flag = 1;
		pip = pip->next;
	}
	if (!flag)
	{
		printf("lol you are wrong\n");
		return (0);
	}
	tbl->q[idx] = cur;
	while (cur && ft_strcmp(cur->name, tbl->end->name))
	{
		add_to_queue(tbl, cur);
		cur = tbl->q[++idx];
	}
	if (!tbl->q[idx])
		return (-1);
	return (idx);
}
