#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

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
node* find_node(node* list);
bool check_avtomorf(int num);
int create_random_num(int num);
void insert_node(list& list, node* next, node* n);
void remove_node(list& list, node* n);
void print_list(const list& list, ostream& ost);
void print_list_rev(const list& list, ostream& ost);

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

	srand(time(nullptr));
	node* current = find_node(list.last);
	
	if (current != list.first)
	{
		for (int i = 0; i < 3; i++)
		{
			insert_node(list, current, init(create_random_num(current->number)));
		}
		amount += 3;
	}

	cout << "List after the change:" << endl;
	print_list(list, cout);
	print_list_rev(list, cout);

	int run;
	cout << "Want to delete an item? (1 - Yes; 0 - No): ";
	cin >> run;

	switch (run) 
	{
	case 1:
		do
		{
			cout << "Enter the index of the number to delete (from 1 before " << amount << "): ";
			cin >> num;
		} while (num > amount || num < 1);
		
		current = list.first;
		for (int i = 1; i < num; ++i) 
		{
			current = current->rlink;
		}
		remove_node(list, current);

		cout << "List after the delete:" << endl;
		print_list(list, cout);
		print_list_rev(list, cout);
		break;
	default:
		return 0;
	}
}

node* init(int num)
{
	node* new_node = new node;
	new_node->number = num;
	new_node->rlink = nullptr;
	new_node->llink = nullptr;

	return new_node;
}

node* find_node(node* first)
{
	while (first != nullptr)
	{
		if (check_avtomorf(first->number))
		{
			break;
		}
		first = first->llink;
	}
	return first;
}

bool check_avtomorf(int num)
{
	int squr = num * num, a = num;

	while (a > 0)
	{
		if (a % 10 == squr % 10)
		{
			a = a / 10;
			squr = squr / 10;
		}
		else return false;
	}
	return true;
}

int create_random_num(int num)
{
	int radical = floor(sqrt(num));
	return (rand() % radical);
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