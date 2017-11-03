#pragma once
#include <string>
#include <vector>

namespace Workflow::Workers {
	class BaseWorker {
	protected:
		int _id;
		std::vector<std::string> _args;
	public:
		BaseWorker();
		BaseWorker(const BaseWorker&);
		BaseWorker(int id, std::vector<std::string> args);

		int GetId();
		std::vector<std::string> GetArgs();
		virtual unsigned int GetValidArgsNumber();
		virtual std::string Execute(std::string input);
	};
}