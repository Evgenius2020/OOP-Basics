#include "Date.h"
#include <ctime> 

using namespace DateTools;

enum FieldName {
	Year = 0,
	Mon = 1,
	Day = 2,
	Hours = 3,
	Minutes = 4,
	Seconds = 5
};
	
static const uint limits[6][2] = { {1, 9999}, { 1, 12 }, {0, 0}, {0, 23}, {0,59}, {0, 59} };

int normalizeNumber(int &source, uint minimum, uint maximun);
uint getMonthDays(Month month, uint year);

void Date::normalizeDate() {
	FieldName currField = Year;
	int carry = 0;
	uint minimum, maximum;
	while(1) {
		if (currField != Day) {
			minimum = limits[currField][0];
			maximum = limits[currField][1];
		}
		else {
			minimum = 1;
			maximum = getMonthDays((Month)fields[Mon], fields[Year]);
		}
		fields[currField] += carry;
		carry = normalizeNumber(fields[currField], minimum, maximum);
		if (carry) {
			if (currField != Year) {
				currField = (FieldName)((int)currField - 1);
			}
		}
		else {
			if (currField == Seconds) {
				return;
			}
			currField = (FieldName)((int)currField + 1);
		}
	}
}

Date::Date() {
	time_t rawtime;
	time(&rawtime);
	struct tm ptm;
	gmtime_s(&ptm, &rawtime);

	this->fields[Year] = ptm.tm_year + 1900;
	this->fields[Mon] = ptm.tm_mon + 1;
	this->fields[Day] = ptm.tm_mday;
	this->fields[Hours] = ptm.tm_hour;
	this->fields[Minutes] = ptm.tm_min;
	this->fields[Seconds] = ptm.tm_sec;
}

Date::Date(const Date& date) {
	for (int i = 0; i < 6; i++) {
		this->fields[i] = date.fields[i];
	}
}

Date::Date(uint year, enum Month month, uint day, uint hours, uint minutes, uint seconds) {
	this->fields[Year] = year;
	this->fields[Mon] = month;
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

void Date::operator=(Date const date) {
	for (int i = 0; i < 5; i++) {
		this->fields[i] = date.fields[i];
	}
}

uint Date::getYear() const {
	return this->fields[Year];
}

uint Date::getMonth() const {
	return this->fields[Mon];
}

uint Date::getDay() const {
	return this->fields[Day];
}

uint Date::getHours() const {
	return this->fields[Hours];
}

uint Date::getMinutes() const {
	return this->fields[Minutes];
}

uint Date::getSeconds() const {
	return this->fields[Seconds];
}

Date& Date::addYears(int years) {
	this->fields[Year] += years;
	normalizeDate();
	return Date(*this);
}

Date& Date::addMonths(int months) {
	this->fields[Mon] += months;
	normalizeDate();
	return Date(*this);
}

Date& Date::addDays(int days) {
	this->fields[Day] += days;
	normalizeDate();
	return Date(*this);
}

Date& Date::addHours(int hours) {
	this->fields[Hours] += hours;
	normalizeDate();
	return Date(*this);
}

Date& Date::addMinutes(int minutes) {
	this->fields[Minutes] += minutes;
	normalizeDate();
	return Date(*this);
}

Date& Date::addSeconds(int seconds) {
	this->fields[Seconds] += seconds;
	normalizeDate();
	return Date(*this);
}

int normalizeNumber(int& source, uint minimum, uint maximum) {
	int carry = 0;

	if (source > maximum) {
		carry = source / maximum;
		source = source % maximum;
	}
	else {
		while (source < minimum) {
			carry--;
			source += (maximum - minimum);
		}
	}

	return carry;
}

uint getMonthDays(Month month, uint year) {
	if (month == Feb) {
		if (year % 400 == 0) {
			return 28;
		}
		if ((year % 4 == 0) || (year % 100 == 0)) {
			return 29;
		}
	}
	if ((month == Apr) || (month == Jun) || (month == Sep) || (month == Nov)) {
		return 30;
	}
	return 31;
}