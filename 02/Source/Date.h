#pragma once
#include <string>
typedef unsigned int uint;

namespace DateTools {
	enum Month {
		Jan = 1, 
		Feb = 2, 
		Mar = 3,
		Apr = 4,
		May = 5,
		Jun = 6,
		Jul = 7,
		Aug = 8,
		Sep = 9,
		Oct = 10,
		Nov = 11,
		Dec = 12
	};

	class Date {
	private:
		void normalizeDate();
		int fields[6];
	public:
		Date();
		Date(const Date& date);
		Date(uint year, Month month, uint day, uint hours, uint minutes, uint seconds);
		Date(uint year, Month month, uint day);
		Date(uint hours, uint minutes, uint seconds);

		uint getYear() const;
		Month getMonth() const;
		uint getDay() const;
		uint getHours() const;
		uint getMinutes() const;
		uint getSeconds() const;
		
		const Date addYears(int years);
		const Date addMonths(int months);
		const Date addDays(int days);
		const Date addHours(int hours);
		const Date addMinutes(int minutes);
		const Date addSeconds(int seconds);

		std::string toString() const;
	};
}