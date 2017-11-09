#include <vector>
#include "gtest.h"
#include "InputMetadata.h"
#include "WorkflowBuilder.h"
#include "InputWorker.h"
#include "OutputWorker.h"

using namespace Building;
using namespace Workers;

TEST(WorkflowBuilderTests, AppendingWorkers) {
	InputMetadata inputMetadata;
	inputMetadata = {
		"in.txt",
		"out.txt",
		{},
		{}
	};
	std::vector<BaseWorker*> workflow;
	workflow = WorkflowBuilder::Build(inputMetadata);
	ASSERT_EQ(2, workflow.size());
	BaseWorker* worker;

	worker = workflow[0];
	ASSERT_EQ(typeid(*worker), typeid(InputWorker));
	ASSERT_EQ(1, worker->GetArgs().size());
	ASSERT_EQ("in.txt", worker->GetArgs()[0]);

	worker = workflow[1];
	ASSERT_EQ(typeid(*worker), typeid(OutputWorker));
	ASSERT_EQ(1, worker->GetArgs().size());
	ASSERT_EQ("out.txt", worker->GetArgs()[0]);
}