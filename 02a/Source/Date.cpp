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

static const int limits[6][2] = { {1, 9999}, { 1, 12 }, {1, 0}, {0, 23}, {0,59}, {0, 59} };

uint getMonthDays(Month month, uint year);

void Date::normalizeDate() {
	FieldName currField = Year;

	while (1) {
		int carry = 0;
		int minimum = limits[currField][0];
		int maximum = (currField != Day) ? limits[currField][1] : getMonthDays((Month)fields[Mon], fields[Year]);
		if (fields[currField] < minimum) {
			carry = -1;
			fields[currField] += maximum + 1 - minimum;
		}
		else if (fields[currField] > maximum) {
			carry = 1;
			fields[currField] -= maximum + 1 - minimum;
		}
		if ((carry) && (currField != Year)) {
			currField = FieldName(currField - 1);
			fields[currField] += carry;
		}
		else {
			if (currField == Seconds) {
				return;
			}
			currField = FieldName(currField + 1);
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

	this->normalizeDate();
}

Date::Date(uint year, enum Month month, uint day) :
	Date::Date(year, month, day, 0, 0, 0) {
	this->normalizeDate();
}

Date::Date(uint hours, uint minutes, uint seconds) : Date() {
	this->fields[Hours] = hours;
	this->fields[Minutes] = minutes;
	this->fields[Seconds] = seconds;
	this->normalizeDate();
}

uint Date::getYear() const {
	return this->fields[Year];
}

Month Date::getMonth() const {
	return (Month)this->fields[Mon];
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
	this->normalizeDate();
	return Date(*this);
}

Date& Date::addMonths(int months) {
	this->fields[Mon] += months;
	this->normalizeDate();
	return Date(*this);
}

Date& Date::addDays(int days) {
	this->fields[Day] += days;
	this->normalizeDate();
	return Date(*this);
}

Date& Date::addHours(int hours) {
	this->fields[Hours] += hours;
	this->normalizeDate();
	return Date(*this);
}

Date& Date::addMinutes(int minutes) {
	this->fields[Minutes] += minutes;
	this->normalizeDate();
	return Date(*this);
}

Date& Date::addSeconds(int seconds) {
	this->fields[Seconds] += seconds;
	this->normalizeDate();
	return Date(*this);
}

uint getMonthDays(Month month, uint year) {
	if (month == Feb) {
		if ((year % 4) || (year % 400 == 0)) {
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