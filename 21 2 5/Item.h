#include <iostream>
#include <string>
#include <iomanip>
#include <QTextStream>

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
    const string GetVisit() const
    {
        if (visit == true)
        {
            return "Visit";
        }
        else
        {
            return "Not visit";
        }
    }
    const int &GetKurs() const
    {
        return kurs;
    }
    const int &GetAge() const
    {
        return age;
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

    static void print_table_head(QTextStream &ost)
    {
        ost << qSetFieldWidth(30) << Qt::left << "Lastname" << "Age" << "Kurs" << "Visit" << qSetFieldWidth(0) << "\n";
    }

    void print_table_row(QTextStream &ost) const
    {
        ost << qSetFieldWidth(30) << Qt::left << GetLast_name().c_str() <<GetAge() << GetKurs() << GetVisit().c_str() << qSetFieldWidth(0) << "\n";
    }
};
