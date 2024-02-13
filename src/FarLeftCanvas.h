#pragma once
#include <gui/View.h>
#include <gui/Image.h>
#include <gui/ImageView.h>
#include <gui/SplitterLayout.h>
#include "MiddleCanvas.h"

//-------------------izbrisati sliku etf (tu samo da se nesto prikazuje)!!!
class FarLeftCanvas : public gui::Canvas
{
private:
protected:
    gui::Image _etf;
    MiddleCanvas* _middleCanvas;
public:
    FarLeftCanvas( MiddleCanvas* canvas)
        : _etf(":ETF")
     //   , _middleCanvas(canvas)
    {
        _middleCanvas = canvas;
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
            gui::Point cp(sz.width / 2, sz.height / 2);
            td::INT4 x = cp.x;
            td::INT4 y = cp.y;

            gui::Rect imgRect(x - 15 - x / 4, y - 15 - y / 4, x + 15 + x / 4, y + 15 + y / 4);
            _etf.draw(imgRect, gui::Image::AspectRatio::Keep, td::HAlignment::Center, td::VAlignment::Center);
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