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

#include "Documents/Documents.h"

namespace CodeSmithy
{

Documents::Documents()
{
}

Documents::~Documents()
{
}

size_t Documents::size() const
{
    return m_documents.size();
}

std::shared_ptr<const Document> Documents::operator[](size_t index) const
{
    return m_documents[index];
}

void Documents::add(std::shared_ptr<Document> document)
{
    m_documents.push_back(document);
    notifyAdd(document);
}

void Documents::addObserver(std::weak_ptr<DocumentsObserver> observer)
{
    m_observers.push_back(observer);
}

void Documents::removeObserver(std::weak_ptr<DocumentsObserver> observer)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        if (m_observers[i].lock().get() == observer.lock().get())
        {
            m_observers.erase(m_observers.begin() + i);
            break;
        }
    }
}

const std::vector<std::weak_ptr<DocumentsObserver> >& Documents::observers() const
{
    return m_observers;
}

void Documents::notifyAdd(std::shared_ptr<Document> document)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        std::shared_ptr<DocumentsObserver> observer = m_observers[i].lock();
        if (observer)
        {
            observer->onAdd(*this, document);
        }
    }
}

}
