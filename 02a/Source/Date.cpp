#include "Date.h"

using namespace DateTools;

enum FieldName {
	Year = 0,
	Month = 1,
	Day = 2,
	Hours = 3,
	Minutes = 4,
	Seconds = 5
};

void normalizeDate(FieldName fieldName = FieldName::Seconds);
int normalizeNumber(int &source, uint minimum, uint maximun);
int getMonthDays(enum Month month, uint year);

// Temporary!
Date::Date() : Date(0, 0, 0) {}

Date::Date(const Date& date) {
	for (int i = 0; i < 5; i++) {
		this->fields[i] = date.fields[i];
	}
}

Date::Date(uint year, enum Month month, uint day, uint hours, uint minutes, uint seconds) {
	this->fields[Year] = year;
	this->fields[FieldName::Month] = month;
	this->fields[Day] = day;
	this->fields[Hours] = hours;
	this->fields[Minutes] = minutes;
	this->fields[Seconds] = seconds;
}

Date::Date(uint year, enum Month month, uint day) : 
	Date::Date(year, month, day, 0, 0, 0) {}

Date::Date(uint hours, uint minutes, uint seconds) : Date() {
	this->fields[Hours] = hours;
	this->fields[Minutes] = minutes;
	this->fields[Seconds] = seconds;
}

void Date::operator=(Date date) {
	for (int i = 0; i < 5; i++) {
		this->fields[i] = date.fields[i];
	}
}

uint Date::getYear() const {
	return this->fields[Year];
}

uint DateTools::Date::getMonth() const {
	return this->fields[FieldName::Month];
}

uint DateTools::Date::getDay() const {
	return this->fields[Day];
}
