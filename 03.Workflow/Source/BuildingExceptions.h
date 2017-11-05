#pragma once
#include <string>

namespace Building {
	const std::string NoException = "";
	const std::string DuplicatedBeginLabelException = "Parsing: Workflow file contains more than one entries of 'desc'";
	const std::string DuplicatedEndLabelException = "Parsing: Workflow file contains more than one entries of 'csed'";
	const std::string DuplicatedIdsException = "Parsing: Workflow file contains duplicated ids in workers definition";
	const std::string BeginWithoutEndException = "Parsing: Workflow file contains 'desc', but not contains 'csed'";
	const std::string WrongWorkflowSequenceException = "Parsing: Wrong worklow sequence string";
	const std::string NoAssingingSymbolException = "Parsing: Worker definition must have a separated '=' symbol, placed after id";
	const std::string UnresolvableLineException = "Parsing: Unresolvable string";
	const std::string WorkersWithoutBeginLabelException = "Parsing: File contains workers definition, but 'csed' label was not found";
	const std::string BeginLabelWithoutWorkersException = "Parsing: File contains 'csed' label, but workers definition was not found";
	const std::string SequenceWithoutWorkersException = "Parsing: File contains workflow sequence, but not to contains workers definition";
	const std::string WrongIdException = "Parsing: Wrong worker id";
}