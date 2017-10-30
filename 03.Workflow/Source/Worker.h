#pragma once
#include <string>
#include <vector>

namespace WorkFlow {
	class Worker {
	protected:
		std::vector<std::string> _args;
	public:
		Worker();
		Worker(const Worker&);
		Worker(std::vector<std::string> args);

		std::vector<std::string> getArgs();
		virtual unsigned int getValidArgsNumber();
		virtual std::string execute(std::string input);
	};
}