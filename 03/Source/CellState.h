#pragma once
#include <map>

namespace GameOfLifeModel {
	enum CellState {
		Dead = 0,
		Alive = 1
	};

	static std::map<char, int> CellDeserializationRule = { {'.', 0}, {'*', 1} };
	static std::map<char, int> CellSerializationRule = { { 0, '.' }, { 1, '*'} };
}
