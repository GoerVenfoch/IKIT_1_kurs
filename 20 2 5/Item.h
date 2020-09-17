#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Item {
private:
	string Last_name;
	int age, kurs;
	bool visit;
public:
	Item()
	{
		Last_name = "";
		age = 0;
		kurs = 0;
		visit = false;
	}
	const string GetLast_name() const
	{
		return Last_name;
	}
	const bool GetVisit()const
	{
		return visit;
	}
	const int GetKurs() const
	{
		return kurs;
	}

    void load_txt(istream &ist)
	{
		ist >> Last_name >> age >> kurs;
		string buf_visit, compair = " \"Visit\"";
        getline(ist, buf_visit);

		if (buf_visit == compair)
		{
			visit = true;
		}
		else
		{
			visit = false;
		}
    }

    void load_bin(istream &ist)
	{	
        size_t len = 0;
        ist.read((char*)&len, sizeof(len));
		if (len != 0)
		{
			char* buf = new char[len];
			ist.read(buf, len);
			Last_name = buf;
			delete[]buf;

			ist.read((char*)& age, sizeof(int));
			ist.read((char*)& kurs, sizeof(int));
			ist.read((char*)& visit, sizeof(bool));
		}
    }

    void save_bin(ostream &ost) const
	{
        if(visit == 0) 
		{
            size_t len = Last_name.length() + 1;
            ost.write((char*)&len, sizeof(len));
            ost.write((char*)Last_name.c_str(), len);

            ost.write((char*)&age, sizeof(int));
            ost.write((char*)&kurs, sizeof(int));
            ost.write((char*)&visit, sizeof(bool));
        }
    }

    static void print_table_head(ostream &ost)
	{
		ost.setf(ios::left);
        ost << setw(15) << "Lastname" << setw(15) << "Age" << setw(15) << "Kurs" << setw(15) << " Visit" << endl;
    }

    void print_table_row(ostream &ost) const
	{
		ost.setf(ios::left);
        ost << setw(15) << Last_name << setw(15) << age << setw(15) << kurs;
		switch (visit)
		{
		case 0:
			ost << setw(15) << "Not visit" << endl;
			break;

		case 1: 
			ost << setw(15) << "Visit" << endl;
			break;
		}
    }
};