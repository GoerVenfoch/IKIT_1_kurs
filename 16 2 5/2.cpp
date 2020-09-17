#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct military_department
{
	char Last_name[25];
	int age, kurs;
	bool visit;
};

void save_bin(vector<military_department>& data, ostream& ost);	//сохранение данных в бинарный файл	
vector<military_department>& load_txt(istream& ist, vector<military_department>& data);	//считывание данных из текстового файла
vector<military_department>& load_bin(istream& ist, vector<military_department>& data); //считывание данных из бинарного файла
void print_data(vector<military_department>& data, ostream& ost);	//вывод данных на экран
void sort(vector<military_department>& data);	//сортировка по заданию

int main()
{
	setlocale(LC_ALL, "Russian");
	string Name_file;
	int mode;

	vector<military_department> buffer_data;

	/*Реадизация выбора режима*/
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

			cout << "Введите название создаваемого файла	: ";
			cin >> Name_file;

			ofstream out_bin(Name_file, ios::binary);

			buffer_data = load_txt(ist, buffer_data);
			print_data(buffer_data, cout);

			sort(buffer_data);
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

			buffer_data = load_bin(in_bin, buffer_data);
			print_data(buffer_data, cout);
			buffer_data.clear();
			in_bin.close();
			break;
		}

		default:
			return 0;
		}
	}
}

void save_bin(vector<military_department>& data, ostream& ost)
{
	int data_size;

	data_size = data.size();
	ost.seekp(0, ios::beg);
	ost.write((char*)& data.at(0), sizeof(military_department) * data_size);
}

vector<military_department>& load_txt(istream& ist, vector<military_department>& data)
{
	string buf_visit, compair = " \"Visit\"";
	military_department buffer;

	while (ist >> buffer.Last_name)
	{
		ist >> buffer.age >> buffer.kurs;

		getline(ist, buf_visit);	//Считывает конец строки 

		if (buf_visit == compair) //Сравнивает с эталоном
		{
			buffer.visit = true;
		}
		else buffer.visit = false;

		data.push_back(buffer);	//Помещает данные в конец вектора
	}

	return data;
}

void print_data(vector<military_department>& data, ostream& ost)
{
	int len = data.size();

	ost.setf(ios::left);
	ost << setw(15) << "Last name" << " " << setw(15) << "Age" << " " << setw(15) << "Сourse" << " " << setw(15) << "Visit" << endl;

	for (int i = 0; i < len; i++)
	{
		ost << setw(15) << data.at(i).Last_name << " " << setw(15) << data.at(i).age << " " << setw(15) << data.at(i).kurs << " ";

		if (data.at(i).visit == true)
		{
			ost << setw(15) << "Visit" << endl;
		}
		else
		{
			ost << setw(15) << "Not visit" << endl;
		}
	}
}

void sort(vector<military_department>& data)
{
	int len = data.size();
	military_department sortval;

	for (int i = len - 1; i > 0; i--)//Удаляет все данные о тех кто посещает
	{
		if (data.at(i).visit == true)
		{
			data.erase(data.begin() + i);
			len--;
		}
	}

	for (int i = 0; i < len; i++)	//Сортирует по убыванию курса
		for (int j = 0; j < len; j++)
		{
			if (data.at(j).kurs < data.at(i).kurs)
			{
				sortval = data.at(i);
				data.at(i) = data.at(j);
				data.at(j) = sortval;
			}
		}
}

vector<military_department>& load_bin(istream & ist, vector<military_department> & data)
{
	military_department buf;

	while (ist.read((char*)& buf, sizeof(military_department)))
	{
		data.push_back(buf);
	}
	return data;
}