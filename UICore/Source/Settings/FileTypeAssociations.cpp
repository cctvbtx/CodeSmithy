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

#include "Settings/FileTypeAssociations.h"

namespace CodeSmithy
{

static const char* fileTypeAssociationElementName = "file-type-association";

FileTypeAssociations::FileTypeAssociations()
{
}

FileTypeAssociations::~FileTypeAssociations()
{
}

size_t FileTypeAssociations::size() const
{
    return m_associations.size();
}

std::shared_ptr<const FileTypeAssociation> FileTypeAssociations::operator[](size_t index) const
{
    return m_associations[index];
}

std::shared_ptr<FileTypeAssociation> FileTypeAssociations::operator[](size_t index)
{
    return m_associations[index];
}

std::shared_ptr<FileTypeAssociation> FileTypeAssociations::find(const std::string& documentTypeName)
{
    for (size_t i = 0; i < m_associations.size(); ++i)
    {
        if (m_associations[i]->documentTypeName() == documentTypeName)
        {
            return m_associations[i];
        }
    }
    return std::shared_ptr<FileTypeAssociation>();
}

void FileTypeAssociations::set(std::shared_ptr<FileTypeAssociation> association)
{
    std::shared_ptr<FileTypeAssociation> existingAssociation = find(association->documentTypeName());
    if (!existingAssociation)
    {
        m_associations.push_back(association);
    }
    else
    {
        *existingAssociation = *association;
    }
}

void FileTypeAssociations::remove(const std::string& documentTypeName)
{
    for (size_t i = 0; i < m_associations.size(); ++i)
    {
        if (m_associations[i]->documentTypeName() == documentTypeName)
        {
            m_associations.erase(m_associations.begin() + i);
            break;
        }
    }
}

void FileTypeAssociations::clear()
{
    m_associations.clear();
}

bool FileTypeAssociations::addNewFileTypeAssociations(const DocumentTypes& documentTypes)
{
    bool result = false;
    for (size_t i = 0; i < documentTypes.size(); ++i)
    {
        if (!find(documentTypes[i]->name()))
        {
            std::shared_ptr<FileTypeAssociation> newAssociation = std::make_shared<FileTypeAssociation>(documentTypes[i]->name());
            m_associations.push_back(newAssociation);
            result = true;
        }
    }
    return result;
}

void FileTypeAssociations::load(pugi::xml_node node)
{
    for (pugi::xml_node associationNode = node.child(fileTypeAssociationElementName); 
         associationNode != 0;
         associationNode = associationNode.next_sibling(fileTypeAssociationElementName))
    {
        std::shared_ptr<FileTypeAssociation> newAssociation = std::make_shared<FileTypeAssociation>();
        newAssociation->load(associationNode);
        m_associations.push_back(newAssociation);
    }
}

void FileTypeAssociations::save(pugi::xml_node node) const
{
    while (node.remove_child(fileTypeAssociationElementName))
    {
    }
    for (size_t i = 0; i < m_associations.size(); ++i)
    {
        pugi::xml_node associationNode = node.append_child(fileTypeAssociationElementName);
        m_associations[i]->save(associationNode);
    }
}

}
