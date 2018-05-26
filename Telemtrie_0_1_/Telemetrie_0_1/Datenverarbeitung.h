///////////////////////////////////////////////////////////
//  Datenverarbeitung.h
//  Implementation of the Class Datenverarbeitung
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#if !defined(EA_7C6C7457_6374_4023_A6B3_BBDD266497CB__INCLUDED_)
#define EA_7C6C7457_6374_4023_A6B3_BBDD266497CB__INCLUDED_

class Datenlogger;

#include "Datensatz.h"
#include "datenlogger.h"
//#include "mainwindow.h"

struct atom
{
    int length = 0;
    int newID = 0;
};

struct fromConfig
{
    atom oldID[8];
    bool isEmpty(int x)
    {
        if(oldID[x].length == 0 || oldID[x].newID == 0)
        {
            return true;
        }
        return false;
    }
};

/**
 * @brief The Datenverarbeitung class
 * Die Klasse Datenverarbeitung entpackt den Datenframe auf das vom
 * Datenlogger gewuenschte Datenformat.
 */
class Datenverarbeitung
{

public:

    Datenverarbeitung();
	virtual ~Datenverarbeitung();
    void FrameEntpacken(Datensatz Frame);
    void setup(Datenlogger *Datenlogptr);

    bool doConfig();

    void setOrdnernameConfigfile(QString ordnerNameConfigfile);

    void setPfadConfigfile(QString pfadConfigfile);

private:

    /**
     * @brief ordnerNameConfigfile  Name des Ordners, in dem die Configfiles liegen
     */
    QString ordnerNameConfigfile ="";
    /**
     * @brief pfadConfigfile     Speicherort an welchem die Configfiles gespeichert oder gesucht werden soll.
     */
    QString pfadConfigfile ="";
    /**
     * @brief stringConfigfile     Dateiname von file, welche Configfile beinhaltet.
     */
    QString stringConfigfile = "";

    /**
     * @brief tempDataVector
     * In dem Vector werden alle temporären Datensätze, die aus dem Frame, mit dem QByteArray entnommen wurden, gespeichert
     *
     */
    vector<Datensatz> tempDataVector;
    /**
     * @brief configVector
     * Vector, der die aus der Configfile gelesenen Daten beinhaltet
     * Ein Vector aus Typen "fromConfig", für jede "CANID" einen "fromConfig" Eintrag
     * Ein "fromConfig" Eintrag enthält das array "oldID" enthält 8 "atom",
     *  diese enthalten die ints length und newID.
     * Somit kann jede "CANID" bis zu 8 neue IDs beinhalten
     */
    vector<fromConfig> configVector;

    Datenlogger *datalog;

    void pullOutID(Datensatz Frame);
    void pullOutData(Datensatz Frame);
    void createDatensaetze(Datensatz Frame);

};
#endif // !defined(EA_7C6C7457_6374_4023_A6B3_BBDD266497CB__INCLUDED_)
