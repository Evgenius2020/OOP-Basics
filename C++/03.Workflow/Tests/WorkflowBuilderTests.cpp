#include <vector>
#include <typeinfo>
#include "gtest.h"

#include "Exceptions.h"
#include "InputMetadata.h"
#include "WorkflowBuilder.h"

#include "ReadfileWorker.h"
#include "WritefileWorker.h"
#include "GrepWorker.h"
#include "SortWorker.h"
#include "ReplaceWorker.h"
#include "DumpWorker.h"

using namespace Building;
using namespace Workers;

void testForException(InputMetadata inputMetadata, std::string expectException) {
	std::vector<BaseWorker*> workflow;
	std::string exception = NoException;

	try {
		workflow = WorkflowBuilder::Build(inputMetadata);
	}
	catch (std::string e) {
		exception = e;
	}

	ASSERT_EQ(expectException, exception);
}

TEST(WorkflowBuilderTests, AllWorkersWorkflow) {
	InputMetadata inputMetadata;
	std::map<int, std::vector<std::string>> nonParsedWorkersMap = {
		{ 10,{ "readfile", "in.txt" } },
		{ 20,{ "sort" } },
		{ 30,{ "dump", "buf.txt" } },
		{ 40,{ "grep", "placeholder" } },
		{ 50,{ "replace", "placeholder", "your_text" } },
		{ 60,{ "writefile", "out.txt" } }
	};
	inputMetadata = { "", "", nonParsedWorkersMap,{ 10, 40, 20, 30, 50, 60 } };
	std::map<int, std::string> expectedTypes = {
		{ 10, typeid(ReadfileWorker).name() },
		{ 20, typeid(SortWorker).name() },
		{ 30, typeid(DumpWorker).name() },
		{ 40, typeid(GrepWorker).name() },
		{ 50, typeid(ReplaceWorker).name() },
		{ 60, typeid(WritefileWorker).name() }
	};

	testForException(inputMetadata, NoException);
	std::vector<BaseWorker*> workflow = WorkflowBuilder::Build(inputMetadata);
	BaseWorker* worker;

	ASSERT_EQ(6, workflow.size());
	for (int i = 0; i < 6; ++i) {
		worker = workflow[i];
		int id = worker->GetId();
		std::vector<std::string> args = worker->GetArgs();

		ASSERT_EQ(inputMetadata.WorkflowSequence[i], id);
		ASSERT_EQ(expectedTypes[id], typeid(*worker).name());
		ASSERT_EQ(nonParsedWorkersMap[id].size() - 1, args.size());
		ASSERT_EQ(worker->GetValidArgsNumber(), args.size());
		for (unsigned int j = 0; j < args.size(); ++j) {
			ASSERT_EQ(nonParsedWorkersMap[id][j + 1], args[j]);
		}
	}
}

TEST(WorkflowBuilderTests, AppendingWorkers) {
	InputMetadata inputMetadata;
	inputMetadata = {
		"in.txt",
		"out.txt",
		{ { 3, { "sort" } } },
		{ 3 }
	};
	testForException(inputMetadata, NoException);
	std::vector<BaseWorker*> workflow;
	workflow = WorkflowBuilder::Build(inputMetadata);
	ASSERT_EQ(3, workflow.size());
	BaseWorker* worker;

	worker = workflow[0];
	ASSERT_EQ(typeid(*worker), typeid(ReadfileWorker));
	ASSERT_EQ(-1, worker->GetId());
	ASSERT_EQ(1, worker->GetArgs().size());
	ASSERT_EQ("in.txt", worker->GetArgs()[0]);

	worker = workflow[2];
	ASSERT_EQ(typeid(*worker), typeid(WritefileWorker));
	ASSERT_EQ(-1, worker->GetId());
	ASSERT_EQ(1, worker->GetArgs().size());
	ASSERT_EQ("out.txt", worker->GetArgs()[0]);
}

TEST(WorkflowBuilderTests, UnknownWorkerName) {
	InputMetadata inputMetadata = {
		"in.txt",
		"out.txt",
		{ { 3,{ "bubble_sort" } } },
		{ 3 }
	};
	testForException(inputMetadata, UnknownWorkerNameException + ": 'bubble_sort'");
}

TEST(WorkflowBuilderTests, WrongNumberOfArgsException) {
	InputMetadata inputMetadata = {
		"in.txt",
		"out.txt",
		{{3, {"sort", "bubble_sort"}}},
		{3}
	};
	testForException(inputMetadata, WrongNumberOfArgsException + ": Worker#3");
}

TEST(WorkflowBuilderTests, UnknownWorkerIdException) {
	InputMetadata inputMetadata = {
		"in.txt",
		"out.txt",
		{ { 3,{ "sort"} } },
		{ 1 }
	};
	testForException(inputMetadata, UnknownWorkerIdException + ": Worker#1");
}

TEST(WorkflowBuilderTests, EmptyWorkflowException) {
	InputMetadata inputMetadata = {
		"",
		"",
		{ { 3,{ "sort" } } },
		{}
	};
	testForException(inputMetadata, EmptyWorkflowException);
}

TEST(WorkflowBuilderTests, ReadfileWorkerIsNotFirstException) {
	InputMetadata inputMetadata;
	inputMetadata = {
		"",
		"out.txt",
		{ { 3,{ "sort" } } },
		{ 3 }
	};
	testForException(inputMetadata, ReadfileWorkerIsNotFirstException);

	inputMetadata = {
		"in.txt",
		"out.txt",
		{ {1, {"readfile", "input.txt"}},  { 3,{ "sort" } } },
		{ 1, 3 }
	};
	testForException(inputMetadata, ReadfileWorkerIsNotFirstException);
}

TEST(WorkflowBuilderTests, WritefileWorkerIsNotLastException) {
	InputMetadata inputMetadata;

	inputMetadata = {
		"in.txt",
		"",
		{ { 3,{ "sort" } } },
		{ 3 }
	};
	testForException(inputMetadata, WritefileWorkerIsNotLastException);
	inputMetadata = {
		"in.txt",
		"out.txt",
		{ { 3,{ "sort" } }, { 4,{"writefile", "output.txt"} } },
		{ 3, 4 }
	};
	testForException(inputMetadata, WritefileWorkerIsNotLastException);
}