#include <sstream>
#include "InputParser.h"
#include "BuildingExceptions.h"

namespace Building {
	InputMetadata InputParser::Parse(std::vector<std::string> args) {
		InputMetadata result;
		std::string input = "";
		std::string output = "";
		if (args.size() >= 3) {
			if (args[1] == "-i") {
				result.SpecifiedInput = args[2];
			}
			else if (args[1] == "-o") {
				result.SpecifiedOutput = args[2];
			}
			if (args.size() >= 5) {
				if (args[3] == "-i") {
					result.SpecifiedInput = args[4];
				}
				else if (args[3] == "-o") {
					result.SpecifiedOutput = args[4];
				}
			}
		}
		
		if (args[0] == "") {
			return result;
		}
		std::string currLine;
		std::istringstream iss(args[0]);
		bool haveBeginLabel = false;
		bool haveEndLabel = false;

		while (!iss.eof()) {
			std::getline(iss, currLine);
			if (currLine == "desc") {
				if (haveBeginLabel) {
					throw DuplicatedBeginLabelException;
				}
				haveBeginLabel = true;
			}
			else if (currLine == "csed") {
				if (haveEndLabel) {
					throw DuplicatedEndLabelException;
				}
				else {
					if (result.NonParsedWorkersMap.size() == 0) {
						throw BeginLabelWithoutWorkers;
					}
				}
				haveEndLabel = true;
			}
			else if (currLine.find("->", 0) != std::string::npos) {
				if (result.NonParsedWorkersMap.size() == 0) {
					throw SequenceWithoutWorkers;
				}
				std::istringstream lineStream(currLine);
				int id;
				std::string splitSymbol;
				while (1) {
					lineStream >> id;
					result.WorkflowSequence.push_back(id);
					if (lineStream.eof()) {
						break;
					}
					lineStream >> splitSymbol;
					if (splitSymbol != "->") {
						throw WrongWorkflowSequenceException;
					}
				}
			}
			else if (currLine.find("=", 0) != std::string::npos) {
				if (!haveBeginLabel) {
					throw WorkersWithoutBeginLabel;
				}
				std::istringstream lineStream(currLine);
				int id;
				lineStream >> id;
				if (!result.NonParsedWorkersMap[id].empty()) {
					throw DuplicatedIdsException;
				}
				std::string currWord;
				lineStream >> currWord;
				if (currWord != "=") {
					throw NoAssingingSymbolException + ": " + currLine;
				}
				while (lineStream >> currWord) {
					result.NonParsedWorkersMap[id].push_back(currWord);
				}
			}
			else {
				throw UnresolvableLineException + ": " + currLine;
			}
		}
		if (haveBeginLabel && !haveEndLabel) {
			throw BeginWithoutEndException;
		}
		
		return result;
	}
}
