#include <sstream>
#include "InputParser.h"
#include "BuildingExceptions.h"
#include "StringHelper.h"

namespace Building {
	InputMetadata InputParser::Parse(std::vector<std::string> args) {
		InputMetadata result;
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

		std::vector<std::string> inputFileLines = Tools::StringHelper::ParseTextToLines(args[0]);
		std::string currLine;
		bool haveBeginLabel = false;
		bool haveEndLabel = false;

		for each (std::string currLine in inputFileLines) {
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
						throw BeginLabelWithoutWorkersException;
					}
				}
				haveEndLabel = true;
			}
			else if (currLine.find("->", 0) != std::string::npos) {
				if (result.NonParsedWorkersMap.size() == 0) {
					throw SequenceWithoutWorkersException;
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
					throw WorkersWithoutBeginLabelException;
				}
				std::istringstream lineStream(currLine);
				std::string currWord;
				lineStream >> currWord;
				int id = atoi(currWord.data());
				if (((id == 0) && (currWord != "0")) || (id < 0)) {
					throw WrongIdException + ": " + currLine;
				}
				if (!result.NonParsedWorkersMap[id].empty()) {
					throw DuplicatedIdsException;
				}
				lineStream >> currWord;
				if (currWord != "=") {
					throw NoAssingingSymbolException + ": " + currLine;
				}
				while (lineStream >> currWord) {
					result.NonParsedWorkersMap[id].push_back(currWord);
				}
				if (result.NonParsedWorkersMap[id].size() == 0) {
					throw EmptyWorkerDefinitionException + ": " + currLine;
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
