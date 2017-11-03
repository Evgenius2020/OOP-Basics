#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Parser.h"
#include "WorkflowBuilder.h"
#include "FileMetadata.h"

namespace Workflow::Building {
	/*FileMetadata WorkflowBuilder::ParseWorkflowFile(std::string path) {
		FileMetadata result;

		std::string currLine;
		std::fstream fs;
		try {
			fs.open(path, std::fstream::in);
			while (1) {
				std::getline(fs, currLine);
				if (currLine == "desc") {
					result.HaveBegin = true;
				}
				else if (currLine == "csed") {
					result.HaveEnd = true;
					break;
				}
				else {
					std::istringstream iss(currLine);
					int id;
					iss >> id;
					if (!result.NonParsedWorkersMap[id].empty()) {
						result.HaveDuplicatedId = true;
					}
					std::string currArg;
					while (iss >> currArg) {
						result.NonParsedWorkersMap[id].push_back(currArg);
					}
				}
			}
		}
		catch (std::ifstream::failure e) {
			std::cerr << "Exception opening/reading/closing file\n";
		}

		return result;
	}*/
}
