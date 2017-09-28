#include "DateHolder.h"
#include "FieldName.h"
#include "Month.h"
#include "uint.h"

using namespace DateTools;

uint DateHolder::getYear() {
	return fields[Year];
}

Month DateHolder::getMonth() {
	return (Month)fields[Mon];
}

uint DateHolder::getDay() {
	return fields[Day];
}

uint DateHolder::getHours() {
	return fields[Hours];
}

uint DateHolder::getMinutes() {
	return fields[Minutes];
}

uint DateHolder::getSeconds() {
	return fields[Seconds];
}