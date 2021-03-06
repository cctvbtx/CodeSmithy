/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "GitRepositoryTests.h"
#include "CodeSmithy/Core/VersionControl/GitRepository.h"
#include <boost/filesystem/operations.hpp>

void GitRepositoryTests::AddTests(TestSequence& testSequence)
{
    TestSequence* gitRepositoryTestSequence = new TestSequence("GitRepository tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *gitRepositoryTestSequence);

    new HeapAllocationErrorsTest("init test 1", InitTest1, *gitRepositoryTestSequence);

    new HeapAllocationErrorsTest("clone test 1", CloneTest1, *gitRepositoryTestSequence);

    new HeapAllocationErrorsTest("open test 1", OpenTest1, *gitRepositoryTestSequence);
    
    new HeapAllocationErrorsTest("checkIfRepository test 1", CheckIfRepositoryTest1, *gitRepositoryTestSequence);
    new HeapAllocationErrorsTest("checkIfRepository test 2", CheckIfRepositoryTest2, *gitRepositoryTestSequence);
}

TestResult::EOutcome GitRepositoryTests::CreationTest1()
{
    CodeSmithy::GitRepository repository;
    return TestResult::ePassed;
}

TestResult::EOutcome GitRepositoryTests::InitTest1(Test& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");
    boost::filesystem::remove_all(outputPath);

    CodeSmithy::GitRepository repository;
    repository.init(outputPath.string())->run().wait();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    return TestResult::ePassed;
}

TestResult::EOutcome GitRepositoryTests::CloneTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_CloneTest1");
    boost::filesystem::remove_all(outputPath);

    CodeSmithy::GitRepository repository;
    repository.clone(inputPath.string(), outputPath.string())->run().wait();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    return TestResult::ePassed;
}

TestResult::EOutcome GitRepositoryTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");

    CodeSmithy::GitRepository repository;
    repository.open(inputPath.string())->run().wait();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    return TestResult::ePassed;
}

TestResult::EOutcome GitRepositoryTests::CheckIfRepositoryTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");

    CodeSmithy::GitRepository repository;
    if (repository.checkIfRepository(inputPath.string()))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome GitRepositoryTests::CheckIfRepositoryTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests");

    CodeSmithy::GitRepository repository;
    if (!repository.checkIfRepository(inputPath.string()))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
