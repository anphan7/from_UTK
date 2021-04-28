#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#include "Person.h"

type_enum str2type(const string &s)
{
	const char *s_d = s.c_str();

	if (strcmp(s_d, "faculty") == 0)
		return FACULTY;
	if (strcmp(s_d, "Assistant Professor") == 0)
		return ASST_PROF;
	if (strcmp(s_d, "Associate Professor") == 0)
		return ASSOC_PROF;
	if (strcmp(s_d, "Full Professor") == 0)
		return FULL_PROF;
	if (strcmp(s_d, "Student") == 0)
		return STUDENT;
	if (strcmp(s_d, "Freshman") == 0)
		return FRESHMAN;
	if (strcmp(s_d, "Sophomore") == 0)
		return SOPHOMORE;
	if (strcmp(s_d, "Junior") == 0)
		return JUNIOR;
	if (strcmp(s_d, "Senior") == 0)
		return SENIOR;

	return UNKNOWN;
}

string type2str(const type_enum &t)
{
	string res = "Unknown";

	switch (t)
	{
		case UNKNOWN:
		case FACULTY:
			res = "faculty";
			break;
		case ASST_PROF:
			res = "Assistant Professor";
			break;
		case ASSOC_PROF:
			res = "Associate Professor";
			break;
		case FULL_PROF:
			res = "Full Professor";
			break;
		case STUDENT:
			res = "Student";
			break;
		case FRESHMAN:
			res = "Freshman";
			break;
		case SOPHOMORE:
			res = "Sophomore";
			break;
		case JUNIOR:
			res = "Junior";
			break;
		case SENIOR:
			res = "Senior";
			break;
	}

	return res;
}

person::person()
{
	name = string(" ");
}

student::student()
{
	name = string(" ");
}

faculty::faculty()
{
	name = string(" ");
}

person::person(const string &n, type_enum t)
{
	name = n;
	type = t;
}

faculty::faculty(const string &n, type_enum t)
{
	name = n;
	type = t;
}

void person::set_type(type_enum mytype)
{
	type = mytype;
}

void person::set_name(string myname)
{
	name = myname;
}

string &person::get_name()
{
	return name;
}

type_enum &person::get_type()
{
	return type;
}

bool person::operator<(const person &rhs)
{

	if (type < 4 && rhs.type > 9)
		return true;
	else if (type > 4 && rhs.type < 9)
		return false;
	else
		return name < rhs.name;
}

ostream &operator<<(ostream &out, person &p)
{

	p.print_person(out);
	p.print_course(out);

	return out;
}

bool faculty::operator<(const faculty &rhs)
{

	if (type == rhs.type)
		return name < rhs.name;
	else if (type < rhs.type)
		return true;
	else
		return false;
}

void faculty::add_course(string &s)
{
	courses.insert(s);
}

void faculty::print_person(ostream &out)
{
	out << setw(12) << right << "Name: "
		<< "Dr. " + name << endl;
	out << setw(12) << right << "Category: " << type2str(type) << endl;
}

void faculty::print_course(ostream &out)
{
	set<string>::iterator it;

	for (it = courses.begin(); it != courses.end(); it++)
	{
		out << setw(12) << right << "Course: " << left << *it << endl;
	}
}

void student::print_person(ostream &out)
{
	out << setw(12) << right << "Name: " << name << endl;
	out << setw(12) << right << "Category: " << type2str(type) << endl;
}

void ::student::add_course(string &name, float gpa)
{
	courses.insert(pair<string, float>(name, gpa));
}

bool student::operator<(const student &rhs)
{
	if (type == rhs.type)
		return name < rhs.name;
	else if (type < rhs.type)
		return true;
	else
		return false;
}

void student::print_course(ostream & out)
{
	map<string, float>::iterator i1;
	float gpa;
	size_t i = 0;
	gpa = 0.0f;

	for (i1 = courses.begin(); i1 != courses.end(); i1++, i++)
	{
		out << setw(12) << right << "Course: " << setw(25) << left << i1->first << " ";
		out << fixed << setprecision(2) << i1->second << " ";
		gpa += i1->second;
		out << fixed << setprecision(2) << (gpa / (i + 1));
		out << endl;
	}
}

