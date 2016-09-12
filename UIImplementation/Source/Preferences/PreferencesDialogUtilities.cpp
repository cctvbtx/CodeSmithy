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

#include "PreferencesDialogUtilities.h"
#include <wx/choice.h>

namespace CodeSmithy
{

wxControl* PreferencesDialogUtilities::createThemeSelectionControl(wxWindow* parent, 
                                                                   wxWindowID id,
                                                                   const std::vector<std::shared_ptr<Theme> >& themes,
                                                                   const std::string& selectedThemeName)
{
    wxArrayString themeChoices;
    size_t selectedThemeIndex = 0;
    for (size_t i = 0; i < themes.size(); ++i)
    {
        themeChoices.Add(themes[i]->name());
        if (themes[i]->name() == selectedThemeName)
        {
            selectedThemeIndex = i;
        }
    }
    wxChoice* themeChoice = new wxChoice(parent, id, wxDefaultPosition, wxDefaultSize, themeChoices);
    themeChoice->SetSelection(selectedThemeIndex);
    return themeChoice;
}

}
