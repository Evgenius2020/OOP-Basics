#include "OutputWorker.h"
#include "StringHelper.h"

namespace Workers {
	OutputWorker::OutputWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> OutputWorker::Execute(std::vector<std::string> input) {
		std::string text = Tools::StringHelper::GenerateTextFromLines(input);
		Tools::StringHelper::PrintTextToFile(_args[0], text);
		return input;
	}
}
