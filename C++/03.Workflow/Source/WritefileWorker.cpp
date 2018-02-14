#include "WritefileWorker.h"
#include "StringHelper.h"

namespace Workers {
	WritefileWorker::WritefileWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> WritefileWorker::Execute(std::vector<std::string> lines) {
		std::string text = Tools::StringHelper::GenerateTextFromLines(lines);
		try {
			Tools::StringHelper::PrintTextToFile(_args[0], text);
		}
		catch (std::string e) {
			throw e;
		}
		return lines;
	}
}