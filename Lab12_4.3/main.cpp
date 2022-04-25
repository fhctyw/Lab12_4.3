#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum class Zodiac { Ram, Bull, Twins, Crab, Lion, Virgin, Balance, Scorpion, Archer, Goat, Water_Bearer, Fish };
string strZodiac[] = { "Ram", "Bull", "Twins", "Crab", "Lion", "Virgin", "Balance", "Scorpion", "Archer", "Goat", "Water_Bearer", "Fish" };
struct Friend
{
	string name, sur_name;
	Zodiac zodiac;
	int date[3];
};

void create_file(string path, Friend* f, size_t cnt)
{
	fstream file(path, ios::out);

	if (file.is_open())
	{
		for (size_t i = 0; i < cnt; i++)
		{
			file.write(f[i].name.c_str(), f[i].name.size());
			file.write(" ", 1);
			file.write(f[i].sur_name.c_str(), f[i].sur_name.size());
			file.write(" ", 1);
			file.write(strZodiac[(int)f[i].zodiac].c_str(), strZodiac[(int)f[i].zodiac].size());
			file.write(" ", 1);
			stringstream ss;
			ss << f[i].date[0] << '.' << f[i].date[1] << '.' << f[i].date[2];
			file.write(ss.str().c_str(), ss.str().size());
			file.write("\n", 1);
		}
	}
	else
		cout << "������� create_file()" << endl;
	file.close();
}

Friend InputFriend()
{
	Friend tmp;
	cout << "������ �������: "; 
	cin.get(); 
	cin.sync();
	getline(cin, tmp.sur_name);
	cout << "������ ��\'�: "; getline(cin, tmp.name);
	int s;
	cout << "������ ���� ������\n(0 - ����, 1 - ������, 2 - ��������, 3 - ���, 4 - ���, 5 - ĳ��, 6 - ������, 7 - �������, 8 - ������, 9 - ������, 10 - ������, 11 - ����): "; cin >> s;
	tmp.zodiac = (Zodiac)s;
	cout << "������ ���� ����������: "; cin >> tmp.date[0];
	cout << "������ ����� ����������: "; cin >> tmp.date[1];
	cout << "������ �� ����������: "; cin >> tmp.date[2];
	return tmp;
}

void Input(Friend*& f, size_t cnt)
{
	f = new Friend[cnt];
	for (size_t i = 0; i < cnt; i++)
		f[i] = InputFriend();
}

void get_from_file(string path, Friend*& f, size_t &cnt)
{
	size_t count_rows = 0;
	fstream file(path, ios::in);
	if (file.is_open()) {
		char ch;
		while (file.get(ch))
			if (ch == '\n')
				count_rows++;
	}
	else
		cout << "������� get_from_file()" << endl;
	file.close();
	cnt = count_rows;
	f = new Friend[count_rows];

	file = fstream(path, ios::in);
	if (file.is_open())
	{
		string line;
		size_t i = 0;
		char ch;
		while (file.get(ch)) {
			if (ch != '\n')
				line += ch;
			else {

				size_t start = 0, end = 0;
				end = line.find(' ', 0);
				f[i].name = line.substr(0, end);
				start = end + 1;
				end = line.find(' ', start);
				f[i].sur_name = line.substr(start, end - start);
				start = end + 1;
				end = line.find(' ', start);
				string zodiac = line.substr(start, end - start);
				for (size_t i1 = 0; i1 < 12; i1++)
					if (strZodiac[i1] == zodiac)
						f[i].zodiac = (Zodiac)i1;
				start = end + 1;
				end = line.find('.', start);
				f[i].date[0] = stoi(line.substr(start, end - start));
				start = end + 1;
				end = line.find('.', start);
				f[i].date[1] = stoi(line.substr(start, end - start));
				start = end + 1;
				end = line.size();
				f[i].date[2] = stoi(line.substr(start, end - start));
				
				i++;
				line = "";
			}

		}
	}
	else
		cout << "������� get_from_file()" << endl;
	file.close();
}

void Display(Friend* f, size_t cnt)
{
	if (f) {
		cout << "----------------------------------------------------------------" << endl;
		cout << "| � |  �������  |   ��\'�   |���� ������| ���� | ����� | �� |" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << left;
		for (size_t i = 0; i < cnt; i++)
		{
			cout << '|' <<
				setw(3) << i + 1 << '|' <<
				setw(12) << f[i].sur_name << '|' <<
				setw(10) << f[i].name << '|' <<
				setw(12) << strZodiac[(int)f[i].zodiac] << '|' <<
				setw(6) << f[i].date[0] << '|' <<
				setw(8) << f[i].date[1] << '|' <<
				setw(5) << f[i].date[2] << '|' << endl;
		}
		cout << "----------------------------------------------------------------" << endl;
	}
	else
		cout << "������� �����" << endl;
	cout << endl;
}

void Add(string path, size_t &cnt)
{
	Friend* tmp;
	get_from_file(path, tmp, cnt);
	cnt++;
	Friend* f = new Friend[cnt];
	for (size_t i = 0; i < cnt-1; i++)
	{
		f[i].name = tmp[i].name;
		f[i].sur_name = tmp[i].sur_name;
		f[i].zodiac = tmp[i].zodiac;
		f[i].date[0] = tmp[i].date[0];
		f[i].date[1] = tmp[i].date[1];
		f[i].date[2] = tmp[i].date[2];
	}
	delete[] tmp;
	f[cnt-1] = InputFriend();
	create_file(path, f, cnt);
	delete[] f;
}

void SearchByZodiac(Friend* f, size_t cnt)
{
	int sign;
	cout << "������ ���� ������: "; cin >> sign;
	size_t c = 0;
	for (size_t i = 0; i < cnt; i++)
		if (f[i].zodiac == (Zodiac)sign)
			c++;

	if (c > 0)
	{
		Friend* tmp = new Friend[c];
		for (size_t i = 0, i1 = 0; i < cnt; i++)
			if (f[i].zodiac == (Zodiac)sign)
				tmp[i1++] = f[i];

		Display(tmp, c);
		delete[] tmp;
	}
	else
		cout << "���� ����� �� ��� ������ ������" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int choice;
	do
	{
		cout << "1 �������� ������" << endl;
		cout << "2 ����������� ������" << endl;
		cout << "3 �������� � ������" << endl;
		cout << "4 ����� �� ������� ������" << endl;
		cout << "choise: "; cin >> choice;

		switch (choice)
		{
		case 1: {
			Friend* friends;
			int c;
			cout << "������ ������� �����: "; cin >> c;
			
			Input(friends, c);
			string path;
			cin.get();
			cout << "������ ����: "; getline(cin, path);
		
			create_file(path, friends, c);
			delete[] friends;
			break;
		}
		case 2: {

			Friend* f;
			string path;
			cin.get();
			cout << "������ ����: "; getline(cin, path);
			size_t cnt;
			get_from_file(path, f, cnt);
			Display(f, cnt);
			delete[] f;
			break;
		}
		case 3: {
			string path;
			cin.get();
			cout << "������ ����: "; getline(cin, path);
			size_t cnt;
			Add(path, cnt);
			break;
		}
		case 4: {
			string path;
			cin.get();
			cout << "������ ����: "; getline(cin, path);
			Friend* f;
			size_t cnt;
			get_from_file(path, f, cnt);
			SearchByZodiac(f, cnt);
			delete[] f;
			break;
		}

		}
		
	} while (choice != 0);

	return 0;
}