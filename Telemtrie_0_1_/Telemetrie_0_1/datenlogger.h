///////////////////////////////////////////////////////////
//  Datenlogger.h
//  Implementation of the Class Datenlogger
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#if !defined(EA_0ACAC0A6_E9C7_4e3b_AAD9_EDA5F2B4DCE3__INCLUDED_)
#define EA_0ACAC0A6_E9C7_4e3b_AAD9_EDA5F2B4DCE3__INCLUDED_

#define ANZAHL_ALLER 999  //Hier ändern falls Logdateien nicht ausreichen

#include "Datensatz.h"
//#include "Datenverarbeitung.h"

#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QDebug>


using namespace std;

/**
 * EIN KOMMENTAR VON MICHA
 * DIESER KOMMENTAR IST FÜR GIT TEST
 * Die Klasse Datenlogger empfaengt den bearbeiteten Datensatz der Klasse
 * Datenverarbeitung.
 * 
 * Die Daten werden in ein Logfile abgespeichert. Als Vorsichtsmassnahme geschieht
 * dies zyklisch, um einen Datenverlust bei Programmabsturz zu verhindern. (z. B.
 * mit QTimer)
 * 
 * Das Logfile kann auch fuer eine spaetere Bearbeitung ausgelesen werden.
 *
 * @todo Alle [] Operationen die mit vectoren zu tun haben, durch .at() ersetzen wegen out of range fehlern
 */
class Datenlogger
{

protected:

public:
	Datenlogger();

	virtual ~Datenlogger();

    void liveAnforderungDaten(int ID);

    void stoppLiveAnforderungDaten(int ID);

    bool logfileLesen(int ID, QTime zeitStart, QTime zeitStop);

    void setOrdnernameDatensatz(QString ordnerNameDatensatz);

	void setPfadDatensatz(QString pfadDatensatz);

    void incomeHandler(Datensatz Frame);

    bool vectorEmpty(int ID);




    Datensatz datenEntnehmen(int ID);

    /**
     * @brief guiIDVector
     * Liste der aktuell Daten die in GUI benutzt wird
     * darf von Klasse Daten aufbereiten gelesen werden
     */
    vector<Datensatz> guiIDVector[ANZAHL_ALLER];

    /**
     * @brief liveIDVector
     * Vector, der 1 oder 0 einthält für live oder nicht live benötigt
     * 1-->live,  0-->nicht live
     */
    int liveIDVector[ANZAHL_ALLER] = {0};

private:
    /**
     * @brief ordnerNameDatensatz  Name des Ordners, in dem die Logfiles liegen
     */
    QString ordnerNameDatensatz ="";
    /**
     * @brief pfadDatensatz     Speicherort an welchem die Daten gespeichert oder gesucht werden sollen.
     */
    QString pfadDatensatz ="";
    /**
     * @brief stringDatensatz     Dateiname von Daten welche Datensaetze beinhaltet.
     */
    QString stringDatensatz = "";
    /**
     * @brief out    Textstream zum schreiben der Logfile
     */
    QTextStream out;
    /**
     * @brief fileDaten    Array aller Logfiles
     */
    QFile fileDaten[ANZAHL_ALLER];

    /**
     * @brief tempsatzDatenEntnehmen
     * Dummy für Funktion Datenentnehmen
     */
    Datensatz tempsatzDatenEntnehmen;


    bool istNeuer(QString neuerSatz, QString alterSatz);                        //Momentan nicht benötigt

    qint64 findeZeilenanfang(int xteZeileDavor, QFile fileDaten[], int frameID);//Momentan nicht benötigt

    bool datenAnListeAnhaengen(Datensatz data);

    bool logfileSchreiben(Datensatz Frame);

    bool logfileErstellen(int ID);

};
#endif // !defined(EA_0ACAC0A6_E9C7_4e3b_AAD9_EDA5F2B4DCE3__INCLUDED_)
