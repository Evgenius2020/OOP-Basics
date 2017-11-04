#pragma once
#include <string>

namespace Building {
	const std::string DuplicatedBeginLabelException = "Parsing: Workflow file contains more than one entries of 'desc'";
	const std::string DuplicatedEndLabelException = "Parsing: Workflow file contains more than one entries of 'csed'";
	const std::string DuplicatedIdsException = "Parsing: Workflow file contains duplicated ids in workers definition";
	const std::string BeginWithoutEndException = "Parsing: Workflow file contains 'desc', but not contains 'csed'";
	const std::string EndWithoutBeginException = "Parsing: Workflow file contains 'csed', bot not contains 'desc'";
	const std::string WrongWorkflowSequenceException = "Parsing: Wrong worklow sequence string";
	const std::string NoAssingingSymbolException = "Parsing: Worker definition doesn't have a separated '=' symbol";
	const std::string UnresolvableLineException = "Parsing: Unresolvable string";
}