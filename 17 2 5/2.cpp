#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

struct list
{
	int number;
	list* link;
};

list* insert_node(list* head, list* prev, list* n); //добавление узла
void print_list(list* first, ostream& ost); //вывод списка
list* init(int num); //инициализация узла
bool check_avtomorf(int num); //проверка на автоморфное число
int create_random_num(int num); //генерация случайного числа
void find_num(list* first, list** past_node); //поиск автоморфного числа

int main()
{
	ifstream ist("Input.txt");

	if (!ist)
	{
		cout << "Unable to open the file." << endl;
		return 1;
	}
	int num;

	list* head = nullptr, *end_node = nullptr, *current = new list;

	while (ist >> num)
	{
		current = init(num);
		head = insert_node(head, end_node, current);
		end_node = current;
	}

	if (head == nullptr)
	{
		cout << "The list is empty." << endl;
		return -1;
	}

	ofstream out("Output.txt");
	srand(time(nullptr));
	print_list(head, out);
	current = nullptr;
	find_num(head, &current);

	if (current != end_node)
	{
		if (current != nullptr)
		{
			num = current->link->number;
		}
		else
		{
			num = head->number;
		}

		for (int i = 0; i < 3; i++)
		{
			head = insert_node(head, current, init(create_random_num(num)));
		}
		print_list(head, out);
		cout << "Check file." << endl;
	}
	else cout << "Number don't found." << endl;

	return 0;
}

list* insert_node(list* head, list* prev, list* n) //Добавляет узел. 
{
	if (head == nullptr)
	{
		head = n;
	}
	else if (prev == nullptr)
	{
		n->link = head;
		head = n;
	}
	else
	{
		n->link = prev->link;
		prev->link = n;
	}
	return head;
}

void print_list(list* first, ostream& ost) //вывод данных
{
	while (first != nullptr)
	{
		ost << first->number << " ";
		first = first->link;
	}
	ost << endl;
}

list* init(int num) //создание нового узла
{
	list* new_node = new list;
	new_node->number = num;
	new_node->link = nullptr;

	return new_node;
}

bool check_avtomorf(int num) //проверка на автоморфность
{
	int squr = pow(num, 2), a = num;

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

int create_random_num(int num) // генерация случайного числа
{
	int radical = floor(sqrt(num));
	return (rand() % radical);
}

void find_num(list* first, list** past_node) //поиск автоморфного числа
{
	while (first != nullptr)
	{
		if (check_avtomorf(first->number))
		{
			break;	
		}
		*past_node = first;
		first = first->link;
	}
}	