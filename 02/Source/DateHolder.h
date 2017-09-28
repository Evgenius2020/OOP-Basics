#pragma once

#include "Month.h"
#include "uint.h"

namespace DateTools {
	class DateHolder {
	protected:
		int fields[6];
	public:
		uint getYear();
		Month getMonth();
		uint getDay();
		uint getHours();
		uint getMinutes();
		uint getSeconds();
	};
}