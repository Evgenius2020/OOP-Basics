#pragma once

#include <string>
#include "uint.h"
#include "Month.h"
#include "DateInterval.h"

namespace DateTools {
	class Date {
	private:
		int fields[6];
		void normalizeDate();
	public:
		Date();
		Date(const Date& date);
		Date(uint year, Month month, uint day, uint hours, uint minutes, uint seconds);
		Date(uint year, Month month, uint day);
		Date(uint hours, uint minutes, uint seconds);
		
		Date addYears(int years) const;
		Date addMonths(int months) const;
		Date addDays(int days) const;
		Date addHours(int hours) const;
		Date addMinutes(int minutes) const;
		Date addSeconds(int seconds) const;

		uint getYear() const;
		Month getMonth() const;
		uint getDay() const;
		uint getHours() const;
		uint getMinutes() const;
		uint getSeconds() const;

		DateInterval getInterval(const Date& another) const;
		Date addInterval(const DateInterval& interval) const;

		std::string toString(const std::string format);
		std::string toString();
	};
}