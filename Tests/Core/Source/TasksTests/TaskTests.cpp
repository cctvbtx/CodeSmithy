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

#include "TaskTests.h"
#include "CodeSmithy/Core/Tasks/Task.h"

using namespace Ishiko::TestFramework;

void TaskTests::AddTests(TestSequence& testSequence)
{
    TestSequence* taskTestSequence = new TestSequence("Task tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *taskTestSequence);
    new HeapAllocationErrorsTest("run test 1", RunTest1, *taskTestSequence);
}

TestResult::EOutcome TaskTests::CreationTest1()
{
    CodeSmithy::Task task;
    return TestResult::ePassed;
}

TestResult::EOutcome TaskTests::RunTest1()
{
    CodeSmithy::Task task;
    boost::unique_future<void> result = task.run();
    if (result.is_ready() && result.has_value())
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
