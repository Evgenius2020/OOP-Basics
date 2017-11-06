#include <iostream>
#include <fstream>
#include "InputWorker.h"

namespace Workers {
	InputWorker::InputWorker(int id, std::vector<std::string>* args) : BaseWorker(id, args) {};

	unsigned int InputWorker::GetValidArgsNumber() {
		return 1;
	}

	std::string InputWorker::Execute(std::string input) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open((*_args)[0], std::fstream::in);
			result = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());;
		}
		catch (std::ifstream::failure e) {
			throw "Exception opening/reading/closing file";
		}
		return result;
	}
}