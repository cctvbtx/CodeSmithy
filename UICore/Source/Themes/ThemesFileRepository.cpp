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

#include "Themes/ThemesFileRepository.h"
#include "ThemesFileRepositoryNode.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>

namespace CodeSmithy
{

static const char* rootElementName = "codesmithy-themes-repository";
static const char* repositoryNameElementName = "name";
static const char* repositoryThemesElementName = "themes";
static const char* themeElementName = "theme";

ThemesFileRepository::ThemesFileRepository(const boost::filesystem::path& repositoryPath)
    : m_path(repositoryPath), m_themesNode(0)
{
    initialize(repositoryPath);
}

ThemesFileRepository::~ThemesFileRepository()
{
}

std::shared_ptr<ThemesRepositoryNode> ThemesFileRepository::addThemeNode(const std::string& name)
{
    if (m_themesNode)
    {
        pugi::xml_node themeNode = m_themesNode.append_child(themeElementName);
        return std::make_shared<ThemesFileRepositoryNode>(themeNode);
    }
    else
    {
        return std::shared_ptr<ThemesRepositoryNode>();
    }
}

void ThemesFileRepository::save()
{
    std::ofstream file(m_path.wstring());
    m_document.save(file);
}

void ThemesFileRepository::initialize(const boost::filesystem::path& repositoryPath)
{
    bool saveNeeded = false;
    if (boost::filesystem::exists(repositoryPath))
    {
    }
    else
    {
        saveNeeded = true;
        pugi::xml_node rootNode = m_document.append_child(rootElementName);
        if (rootNode)
        {
            m_themesNode = rootNode.append_child(repositoryThemesElementName);
        }
    }

    if (saveNeeded)
    {
        save();
    }
}

}
