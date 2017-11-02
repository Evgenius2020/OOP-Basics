#pragma once
#include <string>
#include <vector>

namespace Workflow::Workers {
	class BaseWorker {
	protected:
		std::vector<std::string> _args;
	public:
		BaseWorker();
		BaseWorker(const BaseWorker&);
		BaseWorker(std::vector<std::string> args);

		std::vector<std::string> getArgs();
		virtual unsigned int getValidArgsNumber();
		virtual std::string execute(std::string input);
	};
}