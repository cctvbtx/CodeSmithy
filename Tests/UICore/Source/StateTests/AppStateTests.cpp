/*
    Copyright (c) 2016 Xavier Leclercq

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

#include "AppStateTests.h"
#include "CodeSmithy/UICore/State/AppState.h"
#include <boost/filesystem/operations.hpp>

void AddAppStateTests(TestSequence& testSequence)
{
    TestSequence* appStateTestSequence = new TestSequence("AppState tests", testSequence);

    new FileComparisonTest("Creation test 1", AppStateCreationTest1, *appStateTestSequence);
}

TestResult::EOutcome AppStateCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "StateTests/AppStateCreationTest1.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "StateTests/AppStateCreationTest1.xml");

    CodeSmithy::AppState appState(outputPath);
    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}
