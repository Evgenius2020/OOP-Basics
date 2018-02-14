#include <sstream>
#include <fstream>
#include "StringHelper.h"
#include "Exceptions.h"

namespace Tools {
	std::vector<std::string> StringHelper::ParseTextToLines(std::string text) {
		std::istringstream iss(text);
		std::vector<std::string> result;
		std::string currLine;

		while (!iss.eof()) {
			std::getline(iss, currLine);
			if (iss.fail()) {
				break; // Not useless (try to run the tests without it)
			}
			result.push_back(currLine);
		}

		return result;
	}

	std::string StringHelper::GenerateTextFromLines(std::vector<std::string> lines) {
		std::ostringstream result;
		if (lines.size()) {
			for (unsigned int i = 0; i < lines.size() - 1; ++i) {
				result << lines[i] << std::endl;
			}
			result << lines[lines.size() - 1];
		}

		return result.str();
	}
	std::string StringHelper::GetTextFromFile(std::string path) {
		std::fstream fs;
		std::string result = "";
		fs.open(path, std::fstream::in);
		if (fs.fail()) {
			throw ReadfileErrorException + ": " + path;
		}
		result = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());;
		return result;
	}

	void StringHelper::PrintTextToFile(std::string path, std::string text) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open(path, std::fstream::out);
			fs.write(text.data(), text.length());
		}
		catch (std::ifstream::failure e) {
			throw WritefileErrorException + ": " + path;
		}
	}

	std::string StringHelper::GetEndl() {
		std::ostringstream oss;
		oss << std::endl;
		return oss.str();
	}

	std::string StringHelper::IntToStr(int value) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
}