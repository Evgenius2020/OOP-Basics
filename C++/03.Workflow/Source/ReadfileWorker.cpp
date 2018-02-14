#include "ReadfileWorker.h"
#include "StringHelper.h"

namespace Workers {
	ReadfileWorker::ReadfileWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> ReadfileWorker::Execute(std::vector<std::string> lines) {
		std::string rawText;
		try {
			rawText = Tools::StringHelper::GetTextFromFile(_args[0]);
		}
		catch (std::string e) {
			throw e;
		}
		return Tools::StringHelper::ParseTextToLines(rawText);
	}
}