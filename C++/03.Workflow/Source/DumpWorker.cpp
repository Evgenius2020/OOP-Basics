#include "DumpWorker.h"
#include "StringHelper.h"

namespace Workers {
	DumpWorker::DumpWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	std::vector<std::string> DumpWorker::Execute(std::vector<std::string> lines) {
		std::string text = Tools::StringHelper::GenerateTextFromLines(lines);
		Tools::StringHelper::PrintTextToFile(_args[0], text);

		return lines;
	}
}