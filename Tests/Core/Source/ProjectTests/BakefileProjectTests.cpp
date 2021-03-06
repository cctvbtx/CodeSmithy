/*
    Copyright (c) 2015-2016 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "BakefileProjectTests.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProject.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddBakefileProjectTests(TestSequence& testSequence)
{
	TestSequence* bakefileProjectTestSequence = new TestSequence("BakefileProject tests", testSequence);

	new HeapAllocationErrorsTest("Creation test 1", BakefileProjectCreationTest1, *bakefileProjectTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", BakefileProjectCreationTest2, *bakefileProjectTestSequence);

    new FileComparisonTest("save test 1", BakefileProjectSaveTest1, *bakefileProjectTestSequence);
}

TestResult::EOutcome BakefileProjectCreationTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
	CodeSmithy::BakefileProject project(type, "BakefileProjectCreationTest1");
	return TestResult::ePassed;
}

TestResult::EOutcome BakefileProjectCreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/BakefileProjectCreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("BakefileProject");

    if (projectNode)
    {
        CodeSmithy::DocumentTypes documentTypes;
        CodeSmithy::BakefileProjectType type(documentTypes);
        CodeSmithy::BakefileProject project(type, projectNode);
        if (project.name() == "BakefileProject")
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome BakefileProjectSaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/BakefileProjectSaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/BakefileProjectSaveTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("BakefileProject");
    if (projectNode)
    {
        CodeSmithy::DocumentTypes documentTypes;
        CodeSmithy::BakefileProjectType type(documentTypes);
        CodeSmithy::BakefileProject project(type, projectNode);
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
