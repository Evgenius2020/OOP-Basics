#include "DateInterval.h"
#include "FieldName.h"

using namespace DateTools;

DateInterval::DateInterval() : DateInterval(0, 0, 0, 0, 0, 0) { }

DateInterval::DateInterval(int years, int months, int days, int hours, int minutes, int seconds) {
	fields[Year] = years;
	fields[Mon] = months;
	fields[Day] = days;
	fields[Hours] = hours;
	fields[Minutes] = minutes;
	fields[Seconds] = seconds;
}

DateInterval::DateInterval(const DateInterval & dateInterval) {
	for (int i = 0; i < 6; i++) {
		this->fields[i] = dateInterval.fields[i];
	}
}

int DateInterval::getYears() {
	return fields[Year];
}

int DateInterval::getMonths() {
	return fields[Mon];
}

int DateInterval::getDays() {
	return fields[Day];
}

int DateInterval::getHours() {
	return fields[Hours];
}

int DateInterval::getMinutes() {
	return fields[Minutes];
}

int DateInterval::getSeconds() {
	return fields[Seconds];
}