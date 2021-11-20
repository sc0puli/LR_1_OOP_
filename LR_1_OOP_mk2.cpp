#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Letter
{
public:
	int ind1;		    // индекс получателя
	string adr1;		//адрес получателя
	string name1;		// имя получателя
	string adr2;		// адрес отправителя
	string name2;		// имя отправителя
	double cost;		// стоимость письма
};

class Database
{
public:
	vector<Letter> letters_array;

	const string filepath = "db.txt";
	bool exists;

	void search_by_name2(string);
	void filter_by_index(double); 
	void sort_by_cost(); 
	bool read();
	void write();
	void add(Letter temp);
	void print(); 
};

void Title()
{
	cout << "№";
	cout.width(10);
	cout << "Индекс";
	cout.width(20);
	cout << "Адрес получателя";
	cout.width(20);
	cout << "Имя получателя";
	cout.width(20);
	cout << "Адрес отправителя";
	cout.width(20);
	cout << "Имя отправителя";
	cout.width(20);
	cout << "Стоимость письма" << endl;
}

void print_letter(Letter temp)
{
	cout.width(10);
	cout << temp.ind1;
	cout.width(20);
	cout << temp.adr1;
	cout.width(20);
	cout << temp.name1;
	cout.width(20);
	cout << temp.adr2;
	cout.width(20);
	cout << temp.name2;
	cout.width(20);
	cout << temp.cost << endl;
}

void Database::search_by_name2(string search)
{
	Title();
	for (int i = 0; i < letters_array.size(); i++)
	{
		Letter temp = letters_array[i];
		if (temp.name2 == search)
		{
			cout << i+1;
			print_letter(temp);
		}
	}
}

void Database::filter_by_index(double index_filter)
{
	Title();
	for (int i = 0; i < letters_array.size(); i++)
	{
		Letter temp = letters_array[i];
		if (temp.ind1 > index_filter)
		{
			cout << i+1;
			print_letter(temp);
		}
	}
}

void Database::sort_by_cost()
{
	Title();
	vector<Letter> copy = letters_array;
	struct 
	{
		bool operator()(const Letter t1, const Letter t2)
		{
			return t1.cost < t2.cost;
		}
	}comp;

	sort(copy.begin(), copy.end(), comp);

	for (int i = 0; i < letters_array.size(); i++)
	{
		Letter temp = copy[i];
		cout << i + 1;
		print_letter(temp);
	}
	
}

void Database::add(Letter temp)
{
	letters_array.push_back(temp);
}

void Database::print()
{
	Title();
	for (int i = 0; i < letters_array.size(); i++)
	{
		Letter temp = letters_array[i];
		cout << i+1;
		print_letter(temp);
	
	}
}

bool Database::read()
{
	ifstream input_stream(filepath);

	if (input_stream.fail())
	{
		exists = false;
		return false;
	}
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	exists = true;
	int index;
	string a1, n1, a2, n2;
	double cost;

	while (!input_stream.eof() && !input_stream.fail()) 
	{
		getline(input_stream, a1);
		if (a1.size() == 0) // Баг с чтением пустой строки
		{
			continue;
		}
		getline(input_stream, n1);
		getline(input_stream, a2);
		getline(input_stream, n2);
		input_stream >> index;
		input_stream >> cost;
		if (a1.size() && n1.size() && a2.size() && n2.size())
		{
			Letter temp;
			temp.ind1 = index;
			temp.adr1 = a1;
			temp.name1 = n1;
			temp.adr2 = a2;
			temp.name2 = n2;
			temp.cost = cost;
			letters_array.push_back(temp);
		}
	}

	return true;
}

void Database::write()
{
	ofstream output_stream(filepath);
	for (int i = 0; i < letters_array.size(); i++)
	{
		Letter temp = letters_array[i];
		output_stream << temp.adr1 << "\n"
	                  << temp.name1 << "\n"
					  << temp.adr2 << "\n"
					  << temp.name2 << "\n"
					  << temp.ind1 << "\n"
					  << temp.cost << "\n";
	}
	output_stream.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Database db;

	if (!db.read())
	{
		cout << "Файл с БД отсутствует" << endl;
	}
	else
	{
		cout << "Файл с БД найден" << endl;
	}

	int ch = 1;

	while (ch!=0)
	{
			int cmd;

			cout << endl <<"Выберите команду" << endl;
			cout << "Вывод в виде таблицы = 1";
			cout.width(45); 
			cout << "Добавить новое письмо = 2" << endl;
			cout << "Для поиска по отправителю = 3";
			cout.width(44);
			cout << "Для фильтрации по индексу = 4" << endl;
			cout << "Для сортировки по увеличению стоимости = 5";
			cout.width(40);
			cout << "Завершить процесс и сохранить файл = 6" << endl;
			cout << "Введите номер команды: ";

			cin >> cmd;
			if (cmd < 0)
			{
				cout << "Ошибка. Отрицательный ввод" << endl;
				continue;
			}
			switch (cmd)
			{
				case 1:
					{
						db.print();
						break;
					}
				case 2:
					{
						cout << endl;

						int index;
						string empty, a1, n1, a2, n2;
						double cost;
						cout << "Введите индекс получателя: ";
						cin >> index;
						getline(cin, empty); // баг с чтением пустой строки
						cout << "Введите адрес получателя: ";
						getline(cin, a1);
						cout << "Введите имя получателя: ";
						getline(cin, n1);
						cout << "Введите адрес отправителя: ";
						getline(cin, a2);
						cout << "Введите имя отправителя: ";
						getline(cin, n2);
						cout << "Введите цену: ";
						cin >> cost;

						Letter temp;
						temp.ind1 = index;
						temp.adr1 = a1;
						temp.name1 = n1;
						temp.adr2 = a2;
						temp.name2 = n2;
						temp.cost = cost;
						db.add(temp);
						break;
					}
				case 3:
					{
						string search;
						cout << "Введите имя отправителя для поиска: ";
						getline(cin, search);
						getline(cin, search);
						db.search_by_name2(search);
						break;
					}
				case 4:
					{
						double index_filter;
						cout << "Введите индекс: ";
						cin >> index_filter;
						db.filter_by_index(index_filter);
						break;
					}
				case 5:
					{
						db.sort_by_cost();
						break;
					}
				case 6:
					{
						db.write();
						ch = 0;
						cout << "Файл записан" << endl;
						break;
					}
				default:
					{
						cout << "Введена неверная команда" << endl;
						break;
					}
			}
	}

	cout << "Завершение процесса" << endl;

	return 0;
}