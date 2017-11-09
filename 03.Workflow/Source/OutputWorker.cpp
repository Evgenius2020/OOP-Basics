#include <iostream>
#include <fstream>
#include "OutputWorker.h"

namespace Workers {
	OutputWorker::OutputWorker(int id, std::vector<std::string> args) : BaseWorker(id, args) {}

	unsigned int OutputWorker::GetValidArgsNumber() {
		return 1;
	}

	std::string OutputWorker::Execute(std::string input) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open((_args)[0], std::fstream::out);
			fs.write(input.data(), input.length());
		}
		catch (std::ifstream::failure e) {
			throw "Exception opening/reading/closing file";
		}
		return "";
	}
}
