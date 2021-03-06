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

#include "Settings/GitBashToolSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* executablePathElementName = "executable-path";

GitBashToolSettings::GitBashToolSettings()
    : m_executablePath("C:\\Program Files\\Git\\git-bash.exe")
{
}

GitBashToolSettings::GitBashToolSettings(const GitBashToolSettings& other)
    : m_executablePath(other.m_executablePath)
{
}

GitBashToolSettings& GitBashToolSettings::operator=(const GitBashToolSettings& other)
{
    if (this != &other)
    {
        m_executablePath = other.m_executablePath;
    }
    return *this;
}

GitBashToolSettings::~GitBashToolSettings()
{
}

const std::string& GitBashToolSettings::executablePath() const
{
    return m_executablePath;
}

void GitBashToolSettings::setExecutablePath(const std::string& path)
{
    m_executablePath = path;
}

bool GitBashToolSettings::operator==(const GitBashToolSettings& other) const
{
    return (m_executablePath == other.m_executablePath);
}

bool GitBashToolSettings::operator!=(const GitBashToolSettings& other) const
{
    return !(*this == other);
}

void GitBashToolSettings::load(pugi::xml_node node)
{
    m_executablePath = XMLUtilities::getChildValueAsString(node, executablePathElementName, m_executablePath);
}

void GitBashToolSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, executablePathElementName, m_executablePath);
}

}
