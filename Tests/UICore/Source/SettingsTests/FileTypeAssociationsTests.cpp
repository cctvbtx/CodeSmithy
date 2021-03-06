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

#include "FileTypeAssociationsTests.h"
#include "CodeSmithy/UICore/Settings/FileTypeAssociations.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"

void AddFileTypeAssociationsTests(TestSequence& testSequence)
{
    TestSequence* associationsTestSequence = new TestSequence("FileTypeAssociations tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", FileTypeAssociationsCreationTest1, *associationsTestSequence);

    new HeapAllocationErrorsTest("set test 1", FileTypeAssociationsSetTest1, *associationsTestSequence);
    new HeapAllocationErrorsTest("set test 2", FileTypeAssociationsSetTest2, *associationsTestSequence);

    new HeapAllocationErrorsTest("remove test 1", FileTypeAssociationsRemoveTest1, *associationsTestSequence);
    new HeapAllocationErrorsTest("remove test 2", FileTypeAssociationsRemoveTest2, *associationsTestSequence);

    new HeapAllocationErrorsTest("addNewFileTypeAssociations test 1", FileTypeAssociationsAddNewFileTypeAssociationsTest1,
        *associationsTestSequence);
    new HeapAllocationErrorsTest("addNewFileTypeAssociations test 2", FileTypeAssociationsAddNewFileTypeAssociationsTest2,
        *associationsTestSequence);
    new HeapAllocationErrorsTest("addNewFileTypeAssociations test 3", FileTypeAssociationsAddNewFileTypeAssociationsTest3,
        *associationsTestSequence);
    new HeapAllocationErrorsTest("addNewFileTypeAssociations test 4", FileTypeAssociationsAddNewFileTypeAssociationsTest4,
        *associationsTestSequence);
}

TestResult::EOutcome FileTypeAssociationsCreationTest1()
{
    CodeSmithy::FileTypeAssociations associations;
    if (associations.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsSetTest1()
{
    CodeSmithy::FileTypeAssociations associations;
    std::shared_ptr<CodeSmithy::FileTypeAssociation> association = std::make_shared<CodeSmithy::FileTypeAssociation>("documentType1");
    associations.set(association);
    if ((associations.size() == 1) &&
        (associations[0]->documentTypeName() == "documentType1"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsSetTest2()
{
    CodeSmithy::FileTypeAssociations associations;
    std::shared_ptr<CodeSmithy::FileTypeAssociation> association1 = std::make_shared<CodeSmithy::FileTypeAssociation>("documentType1");
    associations.set(association1);

    std::shared_ptr<CodeSmithy::FileTypeAssociation> association2 = std::make_shared<CodeSmithy::FileTypeAssociation>("documentType1");
    association2->setAssociation(CodeSmithy::FileTypeAssociation::eOpen);
    associations.set(association2);

    if ((associations.size() == 1) &&
        (associations[0]->documentTypeName() == "documentType1") &&
        (associations[0]->association() == CodeSmithy::FileTypeAssociation::eOpen))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsRemoveTest1()
{
    CodeSmithy::FileTypeAssociations associations;
    associations.remove("absent");
    if (associations.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsRemoveTest2()
{
    CodeSmithy::FileTypeAssociations associations;
    std::shared_ptr<CodeSmithy::FileTypeAssociation> association = std::make_shared<CodeSmithy::FileTypeAssociation>("documentType1");
    associations.set(association);
    associations.remove("documentType1");
    if (associations.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsAddNewFileTypeAssociationsTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::FileTypeAssociations associations;
    associations.addNewFileTypeAssociations(documentTypes);
    if (associations.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsAddNewFileTypeAssociationsTest2()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::FileTypeAssociations associations;
    associations.addNewFileTypeAssociations(documentTypes);
    if ((associations.size() == 1) &&
        (associations[0]->documentTypeName() == "Bakefile"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsAddNewFileTypeAssociationsTest3()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());

    CodeSmithy::FileTypeAssociations associations;
    std::shared_ptr<CodeSmithy::FileTypeAssociation> association = std::make_shared<CodeSmithy::FileTypeAssociation>("documentType1");
    associations.set(association);

    associations.addNewFileTypeAssociations(documentTypes);
    if ((associations.size() == 2) &&
        (associations[0]->documentTypeName() == "documentType1") &&
        (associations[1]->documentTypeName() == "Bakefile"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FileTypeAssociationsAddNewFileTypeAssociationsTest4()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());

    CodeSmithy::FileTypeAssociations associations;
    std::shared_ptr<CodeSmithy::FileTypeAssociation> association = std::make_shared<CodeSmithy::FileTypeAssociation>("Bakefile");
    association->setAssociation(CodeSmithy::FileTypeAssociation::eOpen);
    associations.set(association);

    associations.addNewFileTypeAssociations(documentTypes);
    if ((associations.size() == 1) &&
        (associations[0]->documentTypeName() == "Bakefile") &&
        (associations[0]->association() == CodeSmithy::FileTypeAssociation::eOpen))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
