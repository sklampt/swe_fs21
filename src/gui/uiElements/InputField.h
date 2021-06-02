#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <wx/wx.h>
#include <string>


class InputField : public wxPanel {

public:
    InputField(wxWindow* parent, const wxString& labelText, int labelWidth, const wxString& fieldValue, int fieldWidth);
    wxString getValue();
    void setValue(wxString string);

private:
    wxStaticText* _label;
    wxTextCtrl* _field;


};


#endif //INPUTFIELD_H
