#include"stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <mutex>
#include <thread>
#include<conio.h>

using namespace std;

struct Line
{
	Line(char* name, char* surname, int year) :
		name(name),
		surname(surname),
		year(year)
	{}
	char* name;
	char* surname;
	int year;
};

void foo(vector<Line>& db, mutex& mtx)
	{
		while (1)
		{
			//lock_guard<mutex> lock (mtx);
			//Transactions beginning
			mtx.lock();

			db.at(0).year = 2000;
			db.at(1).year = 2000;
			db.at(2).year = 2000;
			db.at(3).year = 2000;
			db.at(4).year = 2000;

			//The end of the transaction
			mtx.unlock();
		}
	}

void bar(vector<Line>& db, mutex& mtx)
{
		while (1)
		{
			//lock_guard<mutex> lock (mtx);
			//Transactions beginning
			mtx.lock();

			db.at(0).year = 1856;
			db.at(1).year = 1879;
			db.at(2).year = 1955;
			db.at(3).year = 1955;
			db.at(4).year = 1984;

			//The end of the transaction
			mtx.unlock();
		}
	}

void viev(vector<Line>& db, mutex& mtx)
	{
		while (1)
		{
			lock_guard<mutex> lock(mtx);

			cout << "Viev: " << endl;
			for (auto row : db) 
			{ 
				cout << row.name<< " " << row.surname << " " <<row.year << ", "; 
			} cout << endl;
			Sleep(100);
		}
	}




/* If you do not use a mutex displaying and modifying the data will not be correct
* Если не использовать мьютексы отображение и модификация данных будут не верными */



int main()
{

	vector<Line> db;
	db.push_back(Line("Nikola", "Tesla", 1856));
	db.push_back(Line("Albert", "Einstein", 1879));
	db.push_back(Line("Bill", "Gates", 1955));
	db.push_back(Line("Stive", "Jobs", 1955));
	db.push_back(Line("Mark", "Zuckerberg", 1984));

	cout << "Hardware concurrency: " << thread::hardware_concurrency() << endl;
	mutex mtx;

	
	thread t1(foo, ref(db), ref(mtx));
	thread t2(bar, ref(db), ref(mtx));
	thread t3(viev, ref(db), ref(mtx));

	t1.detach();
	t2.detach();
	t3.join();
}