#include <iostream>
#include <fstream>

using namespace std;

struct node
{
	int number;
	node* rlink, * llink;
};

struct list
{
	node* first = nullptr;
	node* last = nullptr;
};

node* init(int num);
void insert_node(list& list, node* next, node* n);
void print_list(const list& list_first, ostream& ost);
void print_list_rev(const list& list_last, ostream& ost);
void sort(list& list);
void remove_node(list& list, node* n);

int main()
{
	ifstream ist("Text.txt");
	if (!ist)
	{
		cout << "Unable to open the file." << endl;
		return 1;
	}

	int amount = 0, num;
	list list{};
	while (ist >> num)
	{
		insert_node(list, nullptr, init(num));
		amount++;
	}
	ist.close();
	if (list.first == nullptr || list.last == nullptr)
	{
		cout << "The list is empty." << endl;
		return -1;
	}

	cout << "The list before change:" << endl;
	print_list(list, cout);
	print_list_rev(list, cout);

	sort(list);
	cout << "The list after change:" << endl;
	print_list(list, cout);
	print_list_rev(list, cout);

	return 0;
}

node* init(int num)
{
	node* new_node = new node;
	new_node->number = num;
	new_node->rlink = nullptr;
	new_node->llink = nullptr;

	return new_node;
}

void insert_node(list& list, node* next, node* n)
{
	if (list.first == nullptr || list.last == nullptr)
	{
		n->rlink = nullptr;
		n->llink = nullptr;
		list.first = n;
		list.last = n;
	}
	else if (next == nullptr)
	{
		n->rlink = nullptr;
		n->llink = list.last;
		list.last->rlink = n;
		list.last = n;
	}
	else
	{
		if (next == list.first)
		{
			n->llink = nullptr;
			n->rlink = next;
			next->llink = n;
			list.first = n;
		}
		else
		{
			next->llink->rlink = n;
			n->llink = next->llink;
			next->llink = n;
			n->rlink = next;
		}
	}
}

void print_list(const list& list_first, ostream& ost)
{
	if (list_first.first == nullptr || list_first.last == nullptr)
	{
		ost << "Список пуст!" << endl;
	}
	else
	{
		node* node_print = list_first.first;
		while (node_print != nullptr)
		{
			ost << node_print->number << " ";
			node_print = node_print->rlink;
		}
		ost << endl;
	}
}

void print_list_rev(const list& list_last, ostream& ost)
{
	if (list_last.first == nullptr || list_last.last == nullptr)
	{
		ost << "Список пуст!" << endl;
	}
	else
	{
		node* node_print = list_last.last;
		while (node_print != nullptr)
		{
			ost << node_print->number << " ";
			node_print = node_print->llink;
		}
		ost << endl;
	}
}

void sort(list& first)
{
	list last{};

	while (first.first != nullptr)
	{                   
		node *min = first.first, *p = first.first->rlink;
		while (p != nullptr)
		{
			if (p->number < min->number)
			{
				min = p;
			}
			p = p->rlink;
		}
		remove_node(first, min);
		
		insert_node(last, nullptr, min);
	}
	first.first = last.first;
	first.last = last.last;
}

void remove_node(list& list, node* n)
{
	if (list.first == list.last)
	{
		list.first = nullptr;
		list.last = nullptr;
	}
	else if (list.first == n)
	{
		n->rlink->llink = nullptr;
		list.first = n->rlink;
	}
	else if (list.last == n)
	{
		n->llink->rlink = nullptr;
		list.last = n->llink;
	}
	else
	{
		n->rlink->llink = n->llink;
		n->llink->rlink = n->rlink;
	}
}