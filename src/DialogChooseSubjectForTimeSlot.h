#pragma once
#include <gui/Dialog.h>
#include "ViewChooseSubjectForTimeSlot.h"
#include "Globals.h"
#include <dp/IDatabase.h>

class  DialogChooseSubjectForTimeSlot : public gui::Dialog
{
protected:
    ViewChooseSubjectForTimeSlot _viewTimeSlot;

    bool onClick(Dialog::Button::ID btnID, gui::Button* pButton) override
    {
        if (btnID == Dialog::Button::ID::OK) {
            //  Globals::_IDSubjectSelection = _viewAttendance.getSubjectID();
            return true;
        }
        return false;
    }

public:
    td::INT4 getSubjectID() {
        return  _viewTimeSlot.getSubjectID();
    }
    DialogChooseSubjectForTimeSlot(gui::Frame* pView)
        : gui::Dialog(pView, { {gui::Dialog::Button::ID::OK, tr("Ok"), gui::Button::Type::Default},
                                {gui::Dialog::Button::ID::Cancel, tr("Cancel")} }, gui::Size(300, 100))
    {
        setCentralView(&_viewTimeSlot);
     //   loadComboBox("select b.Naziv_Predmeta  from Korisnici c, Upis a, Predmet b WHERE a.ID_Smjera = b.ID_Smjera AND b.Semestar = a.Semestar AND c.Indeks = a.Indeks AND c.ID = ? ", _viewTimeSlot.getComboBox());
        loadComboBox("select b.Naziv_Predmeta AS Naziv, b.ID_Predmeta AS ID from Korisnici c, UpisPredmet a, Predmet b WHERE a.ID_Predmeta = b.ID_Predmeta AND c.Indeks = a.Indeks  AND c.ID = ? ", _viewTimeSlot.getComboBox());
    }

    bool loadComboBox(td::String select, gui::DBComboBox& combo) {
        dp::IStatementPtr pSelect;
        if (Globals::_currentUserRole == 6) {
            pSelect = dp::getMainDatabase()->createStatement("Select Naziv_Predmeta AS Naziv, ID_Predmeta AS ID FROM Predmet");
        }
        else {
            pSelect = dp::getMainDatabase()->createStatement(select.c_str());
            dp::Params pParams(pSelect->allocParams());
             pParams << Globals::_currentUserID;
        }
        dp::Columns pCols = pSelect->allocBindColumns(2);
        td::String name;
        td::INT4 id;
        pCols << "ID" << id << "Naziv" << name;
        if (!pSelect->execute())
            return false;

        while (pSelect->moveNext())
        {
            combo.addItem(name, id);
        }
        combo.selectIndex(0);
        return true;

    }
    ~DialogChooseSubjectForTimeSlot() {}

};
