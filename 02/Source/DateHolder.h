#pragma once

#include "Month.h"
#include "uint.h"

namespace DateTools {
	class DateHolder {
	protected:
		int fields[6];
	public:
		uint getYear() const;
		Month getMonth() const;
		uint getDay() const;
		uint getHours() const;
		uint getMinutes() const;
		uint getSeconds() const;
	};
}