#include <iostream>
#include <fstream>
#include "OutputWorker.h"

namespace WorkFlow {
	OutputWorker::OutputWorker(std::vector<std::string> args) : Worker(args) {}

	unsigned int OutputWorker::getValidArgsNumber() {
		return 1;
	}

	std::string OutputWorker::execute(std::string input) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open(_args[0], std::fstream::out);
			fs.write(input.data(), input.length());
		}
		catch (std::ifstream::failure e) {
			std::cerr << "Exception opening/reading/closing file\n";
		}
		return "";
	}
}
