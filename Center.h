#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#define FILEPROB cout << "File Error : Could not open the file\n";\
exit(1);
using namespace std;

//int slots[25] = { 0 };


class Center
{
public:char pincode[8], hname[25], state[20], district[30], slots[4];
public:
	char c_code[8];
	int ccount = 0;
	char curr_slots[4];
	void c_unpack(char*);
	void add_slot(char c_id[7], int);
	int c_hash(char*);
	void c_disp(char*);
}cs;



void Center::c_unpack(char* c_id)
{
	fstream file;
	char temp[60];
	int pos = c_hash(c_id);
	file.open("Centers.txt", ios::in | ios::out);
	if (!file)
	{
		FILEPROB;
	}
	file.seekg(pos, ios::beg);
	//cout << file.tellg() << endl;
	file.getline(c_code, 8, '|');
	//cout << c_code << endl;
	file.getline(pincode, 9, '|');
	file.getline(hname, 30, '|');
	file.getline(state, 20, '|');
	file.getline(district, 30, '|');
	file.getline(slots, 4, '|');
	file.getline(temp, 59);
	file.close();
	strcpy(curr_slots, slots);
}


void Center::add_slot(char cid[7], int number)
{
	char buffer[60];
	fstream file;
	c_unpack(cid);
	cout << "Current no. of slots : " << slots << endl;
	number += atoi(slots);
	file.open("Centers.txt", ios::in | ios::out);
	if (!file)
	{
		FILEPROB;
	}
	file.seekg(c_hash(cid), ios::beg);
	strcpy(buffer, cid);
	strcat(buffer, "|");
	strcat(buffer, pincode);
	strcat(buffer, "|");
	strcat(buffer, hname);
	strcat(buffer, "|");
	strcat(buffer, state);
	strcat(buffer, "|");
	strcat(buffer, district);
	strcat(buffer, "|");
	strcat(buffer, _itoa(number, slots, 10));
	strcat(buffer, "|");
	while (strlen(buffer) < 59)
		strcat(buffer, "|");
	cout << "Going to add" << buffer << endl;
	file << buffer << endl;
	file.close();
}


int Center::c_hash(char* id)
{
	int hashval;
	char cid[4];
	strcpy(cid, id+2);
	//cout << cid << endl;
	hashval = atoi(cid) % 100;
	hashval *= 61;
	cout << "Hash val = " << hashval << endl;
	return hashval;
}


void Center::c_disp(char* id)
{
	c_unpack(id);
	cout << "\nCenter Code : " << c_code << endl;
	cout << "\Pincode : " << pincode << endl;
	cout << "\nHospital Name : " << hname << endl;
	cout << "\nState : " << state << endl;
	cout << "\nDistrict : " << district << endl;
	cout << "\nSlots : " << slots << endl;
}