#pragma once

#include "Month.h"
#include "uint.h"

namespace DateTools {
	class DateInterval {
	private:
		int fields[6];
	public:
		DateInterval();
		DateInterval(int years, int months, int days, int hours, int minutes, int seconds);
		DateInterval(const DateInterval& dateInterval);

		int getYears();
		int getMonths();
		int getDays();
		int getHours();
		int getMinutes();
		int getSeconds();
	};
}