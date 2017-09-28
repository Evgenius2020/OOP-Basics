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

int DateInterval::getYears() const {
	return fields[Year];
}

int DateInterval::getMonths() const {
	return fields[Mon];
}

int DateInterval::getDays() const {
	return fields[Day];
}

int DateInterval::getHours() const {
	return fields[Hours];
}

int DateInterval::getMinutes() const {
	return fields[Minutes];
}

int DateInterval::getSeconds() const {
	return fields[Seconds];
}