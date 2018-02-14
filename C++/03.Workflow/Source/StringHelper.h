#pragma once
#include <string>
#include <vector>

namespace Tools {
	class StringHelper {
	public:
		static std::vector<std::string> ParseTextToLines(std::string text);
		static std::string GenerateTextFromLines(std::vector<std::string> lines);

		static std::string GetTextFromFile(std::string path);
		static void PrintTextToFile(std::string path, std::string text);

		static std::string GetEndl();

		static std::string IntToStr(int value);
	};
}