#include <sstream>
#include "InputParser.h"
#include "Exceptions.h"
#include "StringHelper.h"

int generateIdFromString(std::string str, std::string exceptionInfo) {
	int id = atoi(str.data());
	if ((id == 0) && (str != "0")) {
		throw WrongIdException + ": " + exceptionInfo;
	}
	if (id < 0) {
		throw NegativeIdException + ": " + exceptionInfo;
	}
	return id;
}

namespace Building {
	InputMetadata InputParser::Parse(std::string rawWorkflowText, std::vector<std::string> args) {
		InputMetadata result;
		if (args.size() >= 2) {
			if (args[0] == "-i") {
				result.SpecifiedInput = args[1];
			}
			else if (args[0] == "-o") {
				result.SpecifiedOutput = args[1];
			}
			if (args.size() >= 4) {
				if (args[2] == "-i") {
					result.SpecifiedInput = args[3];
				}
				else if (args[2] == "-o") {
					result.SpecifiedOutput = args[3];
				}
			}
		}

		std::vector<std::string> inputFileLines = Tools::StringHelper::ParseTextToLines(rawWorkflowText);
		bool haveBeginLabel = false;
		bool haveWorkersDefinition = false;
		bool haveWorkflowSequence = false;

		for each (std::string currLine in inputFileLines) {
			if (!haveWorkersDefinition) { // Workers definition
				if (currLine == "desc") {
					if (haveBeginLabel) {
						throw DuplicatedBeginLabelException;
					}
					haveBeginLabel = true;
				}
				else if (currLine == "csed") {
					if (result.NonParsedWorkersMap.size() == 0) {
						throw BeginLabelWithoutWorkersException;
					}
					haveWorkersDefinition = true;
				}
				else if (currLine.find("=", 0) != std::string::npos) {
					if (!haveBeginLabel) {
						throw WorkersWithoutBeginLabelException;
					}
					std::stringstream oss(currLine);
					std::string currWord;
					int id;

					oss >> currWord;
					id = generateIdFromString(currWord, currLine);
					if (result.NonParsedWorkersMap[id].size() != 0) {
						throw DuplicatedIdsException + ": " + currLine;
					}

					oss >> currWord;
					if (currWord != "=") {
						throw NoAssingingSymbolException + ": " + currLine;
					}

					while (oss >> currWord) {
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
			else { // Worklow sequence
				if (haveWorkflowSequence) {
					throw SecondSequenceException + ": " + currLine;
				}

				std::stringstream oss(currLine);
				std::string currWord;
				int id;
				bool separationSymbolIsNext = false;
				while (oss >> currWord) {
					if (separationSymbolIsNext) {
						if (currWord != "->") {
							throw WrongWorkflowSequenceException + ": " + currLine;
						}
						separationSymbolIsNext = false;
					}
					else {
						id = generateIdFromString(currWord, currLine);
						result.WorkflowSequence.push_back(id);
						separationSymbolIsNext = true;
					}
				}
				if (!separationSymbolIsNext) {
					throw WrongWorkflowSequenceException + ": " + currLine;
				}

				haveWorkflowSequence = true;
			}
		}

		if (haveBeginLabel && !haveWorkersDefinition) {
			throw BeginWithoutEndException;
		}

		return result;
	}
}