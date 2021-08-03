#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#include "Center.h"
#define FILEPROB cout << "File Error : Could not open the file\n";\
exit(1);
using namespace std;

class Vaccine
{
public: char prid[8], vname, doses, date1[10], date2[10], ccode[7];
public:
	void vaccinate_person(char*, char*, char, char*);
	int v_unpack(char*);
	void v_details(char*);
	int v_hash(char*);
}vs;

int loc_pos;

void Vaccine::vaccinate_person(char* id, char* vid, char vname, char* dt)
{
	char code[7], temp[39];
	int i, pos, cnt, flag;
	fstream file;
	//cout << "Enter the RID : ";
	//cin >> id;
	//cout << "Enter the ID of vaccination center : ";
	//cin >> vid;
	cs.c_unpack(vid);
	if (cs.slots)
	{
		if (v_unpack(id))
		{
			//cout << "Enter date : ";
			//cin >> date2;
			//cout << loc_pos << endl;
			pos = loc_pos;
			file.open("Vaccine.txt", ios::in | ios::out);
			file.seekg(pos, ios::beg);
			file << id << "|" << vname << "|2|" << date1 << "|" << dt << "|" << vid << "|";
			file.close();
		}
		else
		{
			pos = v_hash(id);
			file.open("Vaccine.txt", ios::in | ios::out);
			file.seekg(pos, ios::beg);
			file.getline(temp, 39);
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
			file.open("Vaccine.txt", ios::out | ios::in);
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
				pos = pos + 36;
			}
			else if (cnt == 2)
			{
				file.seekp(pos, ios::beg);
				file.put('3');
				pos = pos + 71;
			}

			//cout << "Enter name of the vaccine : ";
			//cin >> vname;
			//cout << "Enter date : ";
			//cin >> date1;
			//cout << "Inserting at " << pos << endl;
			file.seekp(pos, ios::beg);
			file << id << "|" << vname << "|1|" << dt << "|DD-MM-YY|" << vid << "|";
			file.close();
		}
		cs.add_slot(vid, -1);
	}
	else
		cout << "No slots available\n";
}


int Vaccine::v_hash(char* id)
{
	int hashval = (id[0] + id[2] + id[4]) * (id[1] + id[3] + id[5]);
	hashval %= 40;
	hashval *= 109;
	cout << "Hash val = " << hashval << endl;
	return hashval;
}


int Vaccine::v_unpack(char* id)
{
	int pos, cnt, i, flag = 0;
	fstream file;
	char temp[40], p;
	file.open("Vaccine.txt", ios::in);
	if (!file)
	{
		cout << "File Error : Could not open the file\n";
		exit(1);
	}
	pos = v_hash(id);
	file.seekg(pos, ios::beg);
	file.get(p);
	if (p == '\0')
	{
		file.close();
		return flag;
	}
	cnt = p - 48;
	for (i = 1; i <= cnt; i++)
	{
		loc_pos = file.tellg();
		file.getline(prid, 10, '|');
		file.get(vname);
		file.get(temp[0]);
		file.get(doses);
		file.get(temp[0]);
		file.getline(date1, 10, '|');
		file.getline(date2, 10, '|');
		file.getline(ccode, 6, '|');
		//file.getline(temp, 39);
		if (strcmp(prid, id) == 0)
		{
			flag = 1;
			break;
		}
	}
	file.close();
	return flag;
}


void Vaccine::v_details(char* id)
{
	if (v_unpack(id))
	{
		cout << "Your Vaccination Details are : ";
		if (vs.vname == '0')
			cout << "Vaccine : Covishield";
		else
			cout << "Vaccine : Covaxin";

		cout << "\nNo. of Doses : " << vs.doses << endl;

		cout << "Date of 1st Dose : " << vs.date1 << endl;

		cout << "Date of 2nd Dose : " << vs.date2 << endl;

		cout << "Center Code : " << vs.ccode << endl;
	}
	else
		cout << "Record doesn't exist\n";

}

/*
file.open("Vaccine.txt", ios::in);
if (!file)
{
FILEPROB;
}
file.seekg(pos, ios::beg);
file.getline(temp, 39);
cout << "Got temp : " << temp << endl;
file.close();
if (temp != "")
cnt = temp[0] - 48;
else
cnt = -1;
if (cnt == 3)
{
cout << "Maximum collissions reached\n";
return;
}
file.open("Vaccine.txt", ios::out | ios::in);
if (!file)
{
FILEPROB;
}

if (cnt<0)
{
file.seekp(pos, ios::beg);
file.put('1');
cout << "Enter name of vaccine : ";
cin >> vname;
dos = v[id % 30].doses;
cout << "Enter Date : ";
cin >> dt;
strcpy(temp, vid);
strcat(temp, "|");
file << id << "|" << dos << "|1|" << dt << "|DD-MM-YY-|" << vid << endl;
file.close();
}
else if (cnt == 1)
{
file.seekp(pos, ios::beg);
file.put('2');
pos = pos + 35;
}
else if (cnt == 2)
{
file.seekp(pos, ios::beg);
file.put('3');
pos = pos + 70;
}

file.seekp(pos, ios::beg);
if (cnt < 0)
{

}
*/