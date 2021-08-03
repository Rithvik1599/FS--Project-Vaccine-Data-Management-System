//#include "Person.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<cstdio>
#include "Vaccine.h"
#include "Home.h"
#include "UserOptions.h"
#include "AddSlots.h"
#include "Register.h"
#include "BookSlot.h"
#include "Vaccinate_Person.h"
#include "DeletePerson.h"

#define FILEPROB cout << "File Error : Could not open the file\n";\
exit(1);
using namespace std;


string prid, pname, paadhar, pphoneno, page, pcity, pstate;
string center_id, date_vaccinated, vaccine_name;
string slots, add_slots_no;
int flag2;
namespace Vaccine_GUI {
	int final_seek = 0;
	class Person
	{
		char rid[8], name[25], aadhar_no[14], phone[12], age[4], city[20], state[20];
		int registered_persons = 0;
	public: void add_person();
			int hash(char*);
			void pack();
			int p_unpack(char*);
			void search(char*);
			void del_person(char*);

	}p;


	void Person::add_person()
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
		strcpy(name, pname.c_str());
		strcpy(aadhar_no, paadhar.c_str());
		strcpy(phone, pphoneno.c_str());
		strcpy(age, page.c_str());
		strcpy(city, pcity.c_str());
		strcpy(state, pstate.c_str());
		//strcpy(rid, aadhar_no[0] + aadhar_no[1] + aadhar_no[2] + aadhar_no[10] + aadhar_no[11] + aadhar_no[12]);
		//string str = aadhar_no.substr(0, 3) + aadhar_no.substr(9, 3);
		strncpy(rid, aadhar_no, 3);
		strcat(rid, aadhar_no + 9);
		//cout << rid; - Pass
		pack();
		registered_persons++;
	}

	
	int Person::hash(char* id)
	{
		//int hashval = int(id.at(0) + id.at(2) + id.at(4)) * int(id.at(1) + id.at(3) + id.at(5));
		int hashval = (id[0] + id[2] + id[4]) * (id[1] + id[3] + id[5]);
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
		char temp[100];
		fstream file;
		//itoa(rid, temp, 10);
		char buf[100];
		strcpy(buf, rid);
		strcat(buf, "|");
		strcat(buf, name); 
		strcat(buf, "|"); 
		strcat(buf, aadhar_no); 
		strcat(buf, "|"); 
		strcat(buf, phone);
		strcat(buf, "|"); 
		strcat(buf, age);
		strcat(buf, "|");
		strcat(buf, city); 
		strcat(buf, "|"); 
		strcat(buf, state);
		if (strlen(buf) > 90)
		{
			//cout << "Too large value\n";
			return;
		}
		while (strlen(buf) < 91)
			strcat(buf, "|");

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
		file.getline(temp, 10);
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


	int Person::p_unpack(char* s_rid)
	{
		int pos = hash(s_rid);
		fstream file;
		char temp[100], t;
		int cnt, flag = 0;
		file.open("Persons.txt", ios::in | ios::out);
		if (!file)
		{
			FILEPROB;
		}
		file.seekg(pos, ios::beg);

		file.get(t);
		cnt = t - 48;
		file.seekg(pos + 1, ios::beg);
		for (int i = 1; i <= cnt; i++)
		{
			final_seek = file.tellg();
			file.getline(rid, 10, '|');
			file.getline(name, 25, '|');
			file.getline(aadhar_no, 14, '|');
			file.getline(phone, 12, '|');
			file.getline(age, 4, '|');
			file.getline(city, 20, '|');
			file.getline(state, 20, '|');
			file.getline(temp, 70, '#');
			if (strcmp(s_rid , rid) == 0)
			{
				flag = 1;
				break;
			}
		}
		file.close();
		return flag;

	}


	void Person::search(char* s_rid)
	{
		if (p_unpack(s_rid))
		{
			cout << rid << "\t" << name << "\t" << aadhar_no << "\t" << phone << "\t" << age << "\t" << city << "\t" << state << endl;
			pname = name;
			paadhar = aadhar_no;
			pphoneno = phone;
			page = age;
			pcity = city;
			pstate = state;
			flag2 = 1;
		}
		else
		{
			cout << "Record not found";
			flag2 = 0;
		}

	}


	void Person::del_person(char* id)
	{
		if (p_unpack(id))
		{
			int pos;
			fstream file;
			int i;
			char buf[100] = "";
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
				strcat(buf, "|");
			file.seekg(pos, ios::beg);
			file << buf << "#";
			file.close();
		}
		else
			cout << "Record does not exist\n";
	}
	
	void Register::adper()
	{
		p.add_person();
		
	}

	int BookSlot::search_rid()
	{
		char srid[8];
		strcpy(srid, prid.c_str());
		p.search(srid);
		return flag2;
	}

	void Vaccinate_Person::vaccinate()
	{
		char person_id[8], cent_id[8], va_name[2], va_date[10];
		strcpy(person_id, prid.c_str());
		strcpy(cent_id, center_id.c_str());
		strcpy(va_name, vaccine_name.c_str());
		strcpy(va_date, date_vaccinated.c_str());
		vs.vaccinate_person(person_id, cent_id, va_name[0], va_date);
	}

	void Vaccinate_Person::getSlots()
	{
		char cid[8];
		strcpy(cid, center_id.c_str());
		cs.c_unpack(cid);
		slots = cs.curr_slots;
	}

	void DeletePerson::del_per()
	{
		char id[8];
		strcpy(id, prid.c_str());
		p.del_person(id);
	}

	void AddSlots::getSlots()
	{
		char cid[8];
		strcpy(cid, center_id.c_str());
		cs.c_unpack(cid);
		slots = cs.curr_slots;
	}

	void AddSlots::increase_slots()
	{
		char cid[8], slots[4];
		strcpy(cid, center_id.c_str());
		strcpy(slots, add_slots_no.c_str());
		cs.add_slot(cid, atoi(slots));
	}
}