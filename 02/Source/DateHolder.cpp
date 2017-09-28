#include "DateHolder.h"
#include "FieldName.h"
#include "Month.h"
#include "uint.h"

using namespace DateTools;

uint DateHolder::getYear() const {
	return fields[Year];
}

Month DateHolder::getMonth() const {
	return (Month)fields[Mon];
}

uint DateHolder::getDay() const {
	return fields[Day];
}

uint DateHolder::getHours() const {
	return fields[Hours];
}

uint DateHolder::getMinutes() const {
	return fields[Minutes];
}

uint DateHolder::getSeconds() const {
	return fields[Seconds];
}