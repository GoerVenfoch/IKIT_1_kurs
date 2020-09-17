#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Item.h"
using namespace std;

size_t print_table(const vector<Item>& data, ostream& ost) 
{
	Item::print_table_head(ost);
	for (const Item& item : data) 
	{
		item.print_table_row(ost);
	}
	return 0;
}

size_t load_txt(vector<Item>& data, std::istream& ist) 
{
	int amount = 0;
	string buff;
	while (getline(ist, buff)) 
	{
		amount++;
	}
	ist.clear();
	ist.seekg(0, ios_base::beg);
	for (int i = 0; i < amount; i++) 
	{
		Item item;
		item.load_txt(ist);
		data.push_back(item);
	}
	return amount;
}

size_t load_bin(vector<Item>& data, std::istream& ist) 
{
	int amount = 0;
	for (;!ist.eof();) 
	{
		Item user;
		user.load_bin(ist);
		if (!user.GetLast_name().empty()) 
		{
			data.push_back(user);
			amount++;
		}
	}
	return amount;
}

size_t save_bin(const vector<Item>& data, std::ostream& ost) {
	for (const Item& item : data) {
		item.save_bin(ost);
	}
	return 0;
}

bool comparator(const Item& item1, const Item& item2)
{
	return (item1.GetKurs() > item2.GetKurs());
}

int main() {
	setlocale(LC_ALL, "Russian");
	string Name_file;
	int mode;

	vector<Item> buffer_data;

	while (true)
	{
		cout << "Выберите режим: " << endl << "1 - Первый режим." << endl << "2 - Второй режим." << endl << "0 - Выход" << endl << "Ваш выбор: ";
		cin >> mode;

		switch (mode)
		{
		case 1: // 1 режим
		{
			ifstream ist("MD.txt");
			if (!ist)
			{
				cout << "Файл не найден." << endl;
				return -1;
			}

			cout << "Введите название создаваемого файла: ";
			cin >> Name_file;

			ofstream out_bin(Name_file, ios::binary);

			load_txt(buffer_data, ist);
			print_table(buffer_data, cout);

			sort(buffer_data.begin(), buffer_data.end(), comparator);
			save_bin(buffer_data, out_bin);

			buffer_data.clear();
			out_bin.close();
			break;
		}
		case 2: // 2 режим
		{
			cout << "Введите название открываемого файлa: ";
			cin >> Name_file;

			ifstream in_bin(Name_file, ios::binary);
			if (!in_bin)
			{
				cout << "Файл не найден." << endl;
				return -1;
			}

			load_bin(buffer_data, in_bin);
			print_table(buffer_data, cout);

			buffer_data.clear();
			in_bin.close();
			break;
		}

		default:
			return 0;
		}
	}
}
