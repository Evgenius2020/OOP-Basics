#include <sstream>
#include <fstream>
#include "StringHelper.h"

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
			for (int i = 0; i < lines.size() - 1; ++i) {
				result << lines[i] << std::endl;
			}
			result << lines[lines.size() - 1];
		}

		return result.str();
	}
	std::string StringHelper::GetTextFromFile(std::string path) {
		std::fstream fs;
		std::string result = "";
		try {
			fs.open(path, std::fstream::in);
			result = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());;
		}
		catch (std::ifstream::failure e) {
			throw "Exception opening/reading/closing file";
		}
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
			throw "Exception opening/reading/closing file";
		}
	}

	std::string StringHelper::GetEndl() {
		std::ostringstream oss;
		oss << std::endl;
		return oss.str();
	}
}