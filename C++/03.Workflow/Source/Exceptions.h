#pragma once
#include <string>

const std::string NoException = "";

const std::string BeginLabelWithoutWorkersException = "Parsing: File contains 'csed' label, but workers definition was not found";
const std::string BeginWithoutEndException = "Parsing: Workflow file contains 'desc', but not contains 'csed'";
const std::string DuplicatedBeginLabelException = "Parsing: Workflow file contains more than one entries of 'desc'";
const std::string DuplicatedIdsException = "Parsing: Workflow file contains duplicated ids in workers definition";
const std::string EmptyWorkerDefinitionException = "Parsing: Empty definition of worker";
const std::string NegativeIdException = "Parsing: Id must be non-negative";
const std::string NoAssingingSymbolException = "Parsing: Worker definition must have a separated by a '=' symbol, placed after worker id";
const std::string SecondSequenceException = "Parsing: Two sequence strings found";
const std::string UnresolvableLineException = "Parsing: Unresolvable string at the workers definitions";
const std::string WorkersWithoutBeginLabelException = "Parsing: File contains workers definition, but 'csed' label was not found";
const std::string WrongIdException = "Parsing: Wrong worker id";
const std::string WrongWorkflowSequenceException = "Parsing: Wrong worklow sequence string";

const std::string UnknownWorkerNameException = "Building: Unknown worker name in workers definitions";
const std::string WrongNumberOfArgsException = "Building: Not right number of arguments";
const std::string UnknownWorkerIdException = "Building: Unknown worker id in workflow sequence";
const std::string EmptyWorkflowException = "Building: Empty workflow";
const std::string ReadfileWorkerIsNotFirstException = "Building: The 'readfile' worker must be at the beginning of the sequence";
const std::string WritefileWorkerIsNotLastException = "Building: The 'writefile' worker must be at the end of the sequence";

const std::string ReadfileErrorException = "Running: Error on reading file";
const std::string WritefileErrorException = "Running: Error on writing file";
