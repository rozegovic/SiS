#pragma once
#include <gui/View.h>
#include <gui/Image.h>
#include <gui/ImageView.h>
#include <gui/SplitterLayout.h>
#include "MiddleCanvas.h"
#include <vector>
#include <gui/DrawableString.h>

//-------------------izbrisati sliku etf (tu samo da se nesto prikazuje)!!!
class FarLeftCanvas : public gui::Canvas
{
private:
protected:
    gui::Image _etf;
    MiddleCanvas* _middleCanvas;
    
    //Grupa 2
    gui::Shape _rect;
    std::vector<gui::DrawableString> _subjects;
    
    
public:
    FarLeftCanvas( MiddleCanvas* canvas)
        : _etf(":ETF")
     //   , _middleCanvas(canvas)
    {
       
        _middleCanvas = canvas;
        
        //Grupa 2
       // createStrings();
//        gui::Rect r(50, 50, 200, 150);
//        float lw = 5;
//        _rect.createRect(r, lw);
    }
    
    //Grupa2
    bool createStrings() {
        dp::IStatementPtr pSelect = dp::getMainDatabase()->createStatement("select a.Naziv_Predmeta AS Naziv FROM Predmet a, UpisPredmeta b WHERE b.ID_Studenta = ? AND  b.ID_Predmeta = a.ID_Predmeta");
        dp::Params pParams(pSelect->allocParams());
        pParams << Globals::_currentUserID;
        dp::Columns pCols = pSelect->allocBindColumns(1);
        td::String name;
       // gui::DrawableString drawableName;
        pCols << "Naziv" << name;
        if (!pSelect->execute())
            return false;

        while (pSelect->moveNext()) {
            gui::DrawableString drawableName(name);
            _subjects.push_back(drawableName);
        }
            return false;
    }
    void onDraw(const gui::Rect& rect) override {
        const bool check = false;
        // pogled za profesora i asistenta ------ grupa 3
        if (Globals::_currentUserID == 1 || Globals::_currentUserID == 3) {
            gui::Size sz;
            getSize(sz);
            //gui::Point cp(sz.width / 2, sz.height / 2);
            //td::INT4 x = cp.x;
            //td::INT4 y = cp.y

            //gui::Rect imgRect(x - 15 - x / 4, y - 15 - y / 4, x + 15 + x / 4, y + 15 + y / 4);
            //_etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Center, td::VAlignment::Center); //no

            //--------------------------------------naredna linija zakomentarisana 
            //_pDS = dp::getMainDatabase()->createDataSet("SELECT Korisnici.ID as IDUser, Korisnici.Ime as nameUser, Korisnici.Prezime as surnameUser, Pozicija.ID as positionID, Pozicija.Naziv as roleUser, Korisnici.JMBG as jmbgUser, Korisnici.DatumUpisa as dateEUser, Korisnici.Adresa as addressUser, Korisnici.DatumRodjenja as dateBUser, Korisnici.Indeks as indeksUser FROM Korisnici, Pozicija WHERE Korisnici.PozicijaID = Pozicija.ID AND Korisnici.ID>0", dp::IDataSet::Execution::EX_MULT);
            //ovo treba da se popuni unutrasnjost pravougaonika imenom.


            gui::Rect imgRect(0, 0, sz.width, 100);
            _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Left); //no
            _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Right); //no
            gui::Shape::drawRect(imgRect, td::ColorID::Blue, 2, td::LinePattern::Dot);

            for (int i = 0; i < 3; i++) {
                imgRect.translate(0, 110);
                _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Left);
                gui::Shape::drawRect(imgRect, td::ColorID::Red, 5, td::LinePattern::DashEq);
            }
        }
        // pogled za SAO ------ grupa 1
        else if (Globals::_currentUserID == 4) {
            gui::Size sz;
            getSize(sz);
            gui::Point cp(sz.width / 2, sz.height / 2);
            td::INT4 x = cp.x;
            td::INT4 y = cp.y;

            gui::Rect imgRect(x - 15 - x / 4, y - 15 - y / 4, x + 15 + x / 4, y + 15 + y / 4);
            _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Center, td::VAlignment::Center);
        }
        // pogled za studenta ------ grupa 2
        else if (Globals::_currentUserID == 5) {
            gui::Size sz;
            getSize(sz);
          //  createStrings();
            std::vector<gui::DrawableString> test;
            //for (int i = 0; i < _subjects.size(); i++) {
         //test.push_back(gui::DrawableString(_subjects.at(i))); }

            test.push_back(gui::DrawableString("aaaa"));
            test.push_back(gui::DrawableString("bbbb"));
            test.push_back(gui::DrawableString("cccc"));
            gui::Rect r(0, 0, sz.width, 50);
            gui::Point pt(10, 0);
            float lw = 5;
            _rect.createRect(r, lw);
           // gui::Rect imgRect(450, 50, 650, 150);
            for(auto subj : test){
                gui::Shape::drawRect(r,td::ColorID::WhiteSmoke, td::ColorID::Navy, 4, td::LinePattern::Solid);
                subj.draw(pt, gui::Font::ID::SystemBold, td::ColorID::Navy);
                pt.translate(0,50);
                r.translate(0, 50);
            }
//            gui::Size sz;
//            getSize(sz);
//            gui::Point cp(sz.width / 2, sz.height / 2);
//            td::INT4 x = cp.x;
//            td::INT4 y = cp.y;
//
//            gui::Rect imgRect(x - 15 - x / 4, y - 15 - y / 4, x + 15 + x / 4, y + 15 + y / 4);
//            _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Center, td::VAlignment::Center);
            
        }
        // kada nema ulogovane osobe
       /* else if(Globals::isLogged==check){

        }*/
        else {

        }
    };

    void reset() {
        reDraw();  
    };


    // ideja za implementaciju otvaranja chata
    // treba dodati funkciju za klik
    // vjerovatno treba slati neki parametar i napraviti novu funkciju u middlecanvasu
    //void openMiddleCanvas() {
    //    _middleCanvas->reset();
    //};
   /* void measure(CellInfo& ci) 
    {
        gui::Size imgSize;
        _image.getSize(imgSize);
        ci.minHor = imgSize.width;
        ci.minVer = imgSize.height;
        ci.nResHor = 0;
        ci.nResVer = 0;
    }
    void reMeasure(CellInfo& ci) 
    {
        gui::Size imgSize;
        _image.getSize(imgSize);
        ci.minHor = imgSize.width;
        ci.minVer = imgSize.height;
        ci.nResHor = 0;
        ci.nResVer = 0;
    }*/
};