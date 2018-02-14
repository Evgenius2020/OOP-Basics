#pragma once
#include <string>
#include <vector>

namespace Workers {
	class BaseWorker {
	protected:
		int _id;
		std::vector<std::string> _args;
	public:
		BaseWorker();
		BaseWorker(int id, std::vector<std::string> args);

		int GetId();
		std::vector<std::string> GetArgs();
		virtual unsigned int GetValidArgsNumber();
		virtual std::vector<std::string> Execute(std::vector<std::string> lines);

		~BaseWorker();
	};
}