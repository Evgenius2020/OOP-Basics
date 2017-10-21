#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <math.h>
#include <iterator>
#include "CellState.h"
#include "SquareMatrix.h"
#include "MatrixSerializator.h"

namespace GameOfLifeModel {
	static std::map<CellState, char> CellSerializationRule = { { CellState::Dead, '.' }, { CellState::Alive, '*' } };
	static std::map<char, CellState> CellDeserializationRule = { { '.', CellState::Dead }, { '*', CellState::Alive } };

	std::string MatrixSerializator::Serialize(SquareMatrix matrix) {
		std::stringstream result;
		int size = matrix.getSize();

		for (int y = 0; y < size; ++y) {
			for (int x = 0; x < size; ++x) {
				result << CellSerializationRule[matrix.getXY(x, y)];
			}
			result << std::endl;
		}

		return result.str();
	}

	SquareMatrix MatrixSerializator::Deserialize(const std::string str) {
		int length = str.length();
		std::list<CellState> values;
		
		for (int i = 0; i < length; i++) {
			if (CellDeserializationRule.find(str[i]) != CellDeserializationRule.end()) {
				values.push_front(CellDeserializationRule[str[i]]);
			}
		}

		int size = (int)sqrt(values.size());
		SquareMatrix result(size);
		std::list<CellState>::iterator it = values.begin();

		for (int y = 0; y < size; ++y) {
			for (int x = 0; x < size; ++x) {
				result.setXY(x, y, *it);
				it++;
			}
		}

		return result;
	}

	bool MatrixSerializator::SerializeToFile(SquareMatrix matrix, const std::string path) {
		std::fstream fs;
		fs.open(path, std::fstream::out);
		if (!fs.is_open()) {
			return false;
		}
		std::string data = MatrixSerializator::Serialize(matrix).data();
		fs.write(data.data(), data.length());
		return true;
	}

	SquareMatrix MatrixSerializator::DeserializeFromFile(const std::string path) {
		std::fstream fs;
		fs.open(path, std::fstream::in);
		if (!fs.is_open()) {
			return SquareMatrix();
		}
		std::string data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
		return MatrixSerializator::Deserialize(data);
	}
}