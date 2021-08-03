/*

#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#define FILEPROB cout << "File Error : Could not open the file\n";\
exit(1);
using namespace std;
namespace Vaccine_GUI{
int final_seek = 0;
class Person
{
	string rid, name, aadhar_no, phone, age, city, state;
	int registered_persons = 0;
public: void add_person(string, string, string, string, string, string);
		int hash(string);
		void pack();
		int p_unpack(string);
		void search(string);
		void del_person(string);

}p, ps[30];


void Person::add_person(string pname, string paadhar, string pphone, string page, string pcity, string pstate)
{
	/*cout << "Enter Name : ";
	cin >> name;
	cout << "Enter Aadhar number : ";
	cin >> aadhar_no;
	cout << "Enter phone number : ";
	cin >> phone;
	cout << "Enter Age : ";
	cin >> age;
	cout << "Enter City : ";
	cin >> city;
	cout << "Enter State : ";
	cin >> state;*/
/*
	name = pname;
	aadhar_no = paadhar;
	phone = pphone;
	age = page;
	city = pcity;
	state = pstate;
	//strcpy(rid, aadhar_no[0] + aadhar_no[1] + aadhar_no[2] + aadhar_no[10] + aadhar_no[11] + aadhar_no[12]);
	rid = aadhar_no.substr(0, 3) + aadhar_no.substr(9, 3);
	//cout << rid; - Pass
	pack();
	registered_persons++;
}


int Person::hash(string id)
{
	int hashval = int(id.at(0) + id.at(2) + id.at(4)) * int(id.at(1) + id.at(3) + id.at(5));
	//cout << id.at(0) + id.at(2) + id.at(4) << endl;
	//cout << id.at(1) + id.at(3) + id.at(5) << endl;
	//cout << hashval << endl;
	hashval %= 40;
	//cout << hashval << endl;
	hashval *= 277;
	//cout <<"Hash val = " << hashval << endl;
	return hashval;
}


void Person::pack()
{
	int cnt, pos;
	string temp;
	fstream file;
	//itoa(rid, temp, 10);
	string buf = rid + "|" + name + "|" + aadhar_no + "|" + phone + "|" + age + "|" + city + "|" + state;
	if (buf.length() > 90)
	{
		//cout << "Too large value\n";
		return;
	}
	while (buf.length()<91)
		buf += '|';

	pos = hash(rid);
	//cout << buf << endl;
	//cout << pos << endl;
	file.open("Persons.txt", ios::in);
	if (!file)
	{
		FILEPROB;
	}
	//cout << "File opened" << endl;
	file.seekg(pos, ios::beg);
	//cout << "Seeked" << endl;
	getline(file, temp);
	//cout << "Got temp : " << temp << endl;
	file.close();
	if (temp != "")
		cnt = temp[0] - 48;
	else
		cnt = -1;
	if (cnt == 3)
	{
		//cout << "Maximum collissions reached\n";
		return;
	}
	file.open("Persons.txt", ios::out | ios::in);
	if (!file)
	{
		FILEPROB;
	}
	if (cnt<0)
	{
		file.seekp(pos, ios::beg);
		file.put('1');
		pos = pos + 1;

	}
	else if (cnt == 1)
	{
		file.seekp(pos, ios::beg);
		file.put('2');
		pos = pos + 93;
	}
	else if (cnt == 2)
	{
		file.seekp(pos, ios::beg);
		file.put('3');
		pos = pos + 185;
	}

	//cout << "Inserting at : " << pos << endl;
	file.seekp(pos, ios::beg);
	file << buf << "#";
	file.close();

}


int Person::p_unpack(string s_rid)
{
	int pos = hash(s_rid);
	fstream file;
	string temp;
	int cnt, flag = 0;
	file.open("Persons.txt", ios::in);
	if (!file)
	{
		FILEPROB;
	}
	file.seekg(pos, ios::beg);

	getline(file, temp);
	cnt = temp[0] - 48;
	file.seekg(pos + 1, ios::beg);
	for (int i = 1; i <= cnt; i++)
	{
		final_seek = file.tellg();
		getline(file, rid, '|');
		getline(file, name, '|');
		getline(file, aadhar_no, '|');
		getline(file, phone, '|');
		getline(file, age, '|');
		getline(file, city, '|');
		getline(file, state, '|');
		getline(file, temp, '#');
		if (s_rid == rid)
		{
			flag = 1;
			break;
		}
	}
	file.close();
	return flag;

}


void Person::search(string s_rid)
{
	if (p_unpack(s_rid))
	{
		cout << rid << "\t" << name << "\t" << aadhar_no << "\t" << phone << "\t" << age << "\t" << city << "\t" << state << endl;
	}
	else
		cout << "Record not found";

}


void Person::del_person(string id)
{
	if (p_unpack(id))
	{
		int pos;
		fstream file;
		int i;
		string buf = "";
		char n;
		file.open("Persons.txt", ios::in | ios::out);
		pos = hash(id);
		file.seekg(pos, ios::beg);
		file.get(n);
		file.seekp(pos, ios::beg);
		if (n == '1')
			file.put('0');
		else if (n == '2')
			file.put('1');
		else
			file.put('2');

		pos = final_seek;
		for (i = 0; i < 91; i++)
			buf += "|";
		file.seekg(pos, ios::beg);
		file << buf << "#";
		file.close();
	}
	else
		cout << "Record does not exist\n";
}
}

*/