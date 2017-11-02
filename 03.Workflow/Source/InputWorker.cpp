#include <iostream>
#include <fstream>
#include "InputWorker.h"

namespace Workflow::Workers {
	InputWorker::InputWorker(std::vector<std::string> args) : BaseWorker(args) {};

	unsigned int InputWorker::getValidArgsNumber() {
		return 1;
	}

	std::string InputWorker::execute(std::string input) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open(_args[0], std::fstream::in);
			result = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());;
		}
		catch (std::ifstream::failure e) {
			std::cerr << "Exception opening/reading/closing file\n";
		}
		return result;
	}
}