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

#include "ThemesTestSequence.h"
#include "ThemeTests.h"
#include "EditorThemeTests.h"
#include "ThemesFileRepositoryTests.h"
#include "ThemesTests.h"
#include "BuiltInThemesTests.h"
#include <boost/filesystem/operations.hpp>

void AddThemesTestSequence(TestHarness& theTestHarness)
{
    boost::filesystem::path outputPath(theTestHarness.environment().getTestOutputDirectory() / "ThemesTests");
    boost::filesystem::create_directories(outputPath);

    TestSequence& themesTestSequence = theTestHarness.appendTestSequence("Themes tests");

    AddThemeTests(themesTestSequence);
    AddEditorThemeTests(themesTestSequence);
    AddThemesFileRepositoryTests(themesTestSequence);
    AddThemesTests(themesTestSequence);
    AddBuiltInThemesTests(themesTestSequence);
}
