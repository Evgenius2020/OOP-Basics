#pragma once

namespace DateTools {
	typedef unsigned int uint;
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
	public:
		Date();
		Date(const Date& pattern);
		Date(uint year, Month month, uint day, uint minutes, uint seconds);
		Date(uint year, Month month, uint day);

		Date operator=(Date date);

		uint getYears();
		uint getMonths();
		uint getDays();
		uint getHours();
		uint getMinutes();
		uint getSeconds();

		Date& addYears(int years);
		Date& addMonths(int months);
		Date& addDays(int days);
		Date& addHours(int hours);
		Date& addMinutes(int minutes);
		Date& addSeconds(int seconds);
	};
}