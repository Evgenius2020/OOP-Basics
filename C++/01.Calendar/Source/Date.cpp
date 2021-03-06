#include <ctime> 
#include <sstream>
#include "Date.h"
#include "FieldName.h"

using namespace DateTools;

static const int limits[6][2] = { {1, 9999}, { 1, 12 }, {1, 0}, {0, 23}, {0,59}, {0, 59} };
static const std::string monthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

uint getMonthDays(Month month, uint year);

void Date::normalizeDate() {
	FieldName currField = Year;

	while (1) {
		int carry = 0;
		int minimum = limits[currField][0];
		int maximum = (currField != Day) ? limits[currField][1] : getMonthDays((Month)fields[Mon], fields[Year]);
		if (fields[currField] < minimum) {
			carry = -1;
		}
		else if (fields[currField] > maximum) {
			carry = 1;
		}

		if (carry) {
			if ((currField == Day) && (carry == -1)) {
				maximum = getMonthDays((Month)(fields[Mon] - 1), fields[Year]);
			}
			fields[currField] -= carry * (maximum + 1 - minimum);
			if (currField != Year) {
				currField = FieldName(currField - 1);
				fields[currField] += carry;
			}
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

Date Date::addYears(int years) const {
	Date date = Date(*this);
	date.fields[Year] += years;
	date.normalizeDate();
	return date;
}

Date Date::addMonths(int months) const {
	Date date = Date(*this);
	date.fields[Mon] += months;
	date.normalizeDate();
	return date;
}

Date Date::addDays(int days) const {
	Date date = Date(*this);
	date.fields[Day] += days;
	date.normalizeDate();
	return date;
}

Date Date::addHours(int hours) const {
	Date date = Date(*this);
	date.fields[Hours] += hours;
	date.normalizeDate();
	return date;
}

Date Date::addMinutes(int minutes) const {
	Date date = Date(*this);
	date.fields[Minutes] += minutes;
	date.normalizeDate();
	return date;
}

Date Date::addSeconds(int seconds) const {
	Date date = Date(*this);
	date.fields[Seconds] += seconds;
	date.normalizeDate();
	return date;
}

uint Date::getYear() const {
	return fields[Year];
}

Month Date::getMonth() const {
	return (Month)fields[Mon];
}

uint Date::getDay() const {
	return fields[Day];
}

uint Date::getHours() const {
	return fields[Hours];
}

uint Date::getMinutes() const {
	return fields[Minutes];
}

uint Date::getSeconds() const {
	return fields[Seconds];
}

DateInterval DateTools::Date::getInterval(const Date & another) const {
	int years = another.getYear() - getYear();
	int months = (int)another.getMonth() - (int)getMonth();
	int days = another.getDay() - getDay();
	int hours = another.getHours() - getHours();
	int minutes = another.getMinutes() - getMinutes();
	int seconds = another.getSeconds() - getSeconds();

	return DateInterval(years, months, days, hours, minutes, seconds);
}

Date Date::addInterval(const DateInterval& interval) const {
	Date date(*this);
	date.fields[Year] += interval.getYears();
	date.fields[Mon] += interval.getMonths();
	date.fields[Day] += interval.getDays();
	date.fields[Hours] += interval.getHours();
	date.fields[Minutes] += interval.getMinutes();
	date.fields[Seconds] += interval.getSeconds();
	date.normalizeDate();

	return date;
}

std::string intToString(int val, size_t size) {
	std::stringstream oss;
	oss << "0000";
	oss << val;
	std::string result = oss.str();
	result = result.substr(result.size() - size, size);
	return result;
}

std::string replaceAll(const std::string str, const std::string oldStr, const std::string newStr) {
	std::string result = str;
	int pos;
	size_t len = newStr.length();

	while (0 <= (pos = result.find(oldStr))) {
		result.replace(pos, len, newStr);
	}

	return result;
}

std::string Date::toString(const std::string format) {
	std::string result = format;

	result = replaceAll(result, "YYYY", intToString(getYear(), 4));
	result = replaceAll(result, "MMM", monthNames[getMonth() - 1]);
	result = replaceAll(result, "MM", intToString(getMonth(), 2));
	result = replaceAll(result, "DD", intToString(getDay(), 2));
	result = replaceAll(result, "hh", intToString(getHours(), 2));
	result = replaceAll(result, "mm", intToString(getMinutes(), 2));
	result = replaceAll(result, "ss", intToString(getSeconds(), 2));

	return result;
}

std::string Date::toString() {
	return toString("YYYY-MMM-DD hh::mm::ss");
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