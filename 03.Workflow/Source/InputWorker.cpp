#include "InputWorker.h"
#include "StringHelper.h"

namespace Workers {
	InputWorker::InputWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> InputWorker::Execute(std::vector<std::string> input) {
		std::string rawText = Tools::StringHelper::GetTextFromFile(_args[0]);
		return Tools::StringHelper::ParseTextToLines(rawText);
	}
}