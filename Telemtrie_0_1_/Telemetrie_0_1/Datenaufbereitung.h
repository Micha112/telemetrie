///////////////////////////////////////////////////////////
//  Datenaufbereitung.h
//  Implementation of the Class Datenaufbereitung
//  Created on:      14-Dez-2017 12:09:17
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#if !defined(EA_86BA3343_9565_435f_A3A1_0F129309C661__INCLUDED_)
#define EA_86BA3343_9565_435f_A3A1_0F129309C661__INCLUDED_


#define BOUNDARIELIMIT 300;  //Anzahl der Datenpunkte, die gleichzeitig in die GUI geladen werden, unabhängig von der "Anzeigedauer"

class Datenlogger;

#include "Datensatz.h"
#include "datenlogger.h"


#include <stack>
#include <queue>
#include <vector>
#include <list>
//#include <QTime>
//#include <QFile>
//#include <QDir>
//#include <QTextStream>
//#include <QStringList>
//#include <QDebug>


/**
 * @brief The Datenaufbereitung class
 * Bereitet die Daten für die Anzeige durch die GUI auf. Hinzufügen von Variablenname und Einheit durch eine Configfile.
 * Aussortieren von nicht benötigten Datensätzen. Prüfung auf Plausibilität und Notwendigkeit der Datensätze.
 * Entnimmt die Datensätze aus dem Vectorarray "guiIDVector" der Klasse Datenlogger.
 * Bekommt genau so wie die Klasse "Datenlogger" ebenfalls einen Vector, in dem die IDs abgespeichert sind,
 *  die live benötigt werden. ("liveIDVector")
 * Muss Informationenn darüber erhalten, wie die Angezeigten Variablen aktuell in der GUI skaliert sind,
 *  um Anzeigerate anzupassen (von "Befehls Konfiguration Verarbeitung")
 * Legt der Klasse "Buffer GUI Config" alle fertigen Daten auf ein Vectorarray, wie es im "Datenlogger" auch gemacht wird
 * Die Klasse "Befehls Konfiguration Verarbeitung" bestimmt welche Funktionen mit den einkommenden Daten durchgeführt werden soll
 */
class Datenaufbereitung
{

public:

    /**
     * @brief liveIDVector
     * Vector, der 1 oder 0 einthält für live oder nicht live benötigt
     * 1-->live,  0-->nicht live
     * (kann auch weggelassen werden, da in der Klasse Datelogger der selbe Vector vorhanden ist,
     *  dann muss halt immer dorf nachgeschaut werden)
     */
    int liveIDVector[ANZAHL_ALLER] = {0};

    /**
     * @brief configArray
     * Array, das   das Ausgelesene der Configfile abspeichert in den jeweiligen Datensaetzen,
     *  um es nur hier rauslesen zu müssen und nicht immer aus der Configfile
     */
    Datensatz configArray[ANZAHL_ALLER];
    
    /**
     * @brief overloadArray
     * Array, in dem zu jeder ID eine INT abgespeichert ist, die aussagt, wie viele Datenpakete übersprungen werden sollen
     *  Wird also von der Funktion "editBoundaries" festgelegt. Soll Standartmäßig 1 sein, also alle Daten werden geschickt
     *  Befüllung mit 1 wird im Konstruktor durchgeführt
     */
    int overloadArray[ANZAHL_ALLER];
    
    /**
    * @brief overloadCounterArray
    * Zum Zählen für die Overload Funktionen. Rein funktionell, enthält nur aufzählbare Ints
    * Standartmäßig mit 1 befüllt, damit jeder Datensatz übertragen wird
    */
    int overloadCounterArray[ANZAHL_ALLER] = {0};
    
    /**
     * @brief bufferVector
     * Buffer, der zur GUI weiter gehen wird  
     * 
     * //ERSETZT VILLEICHT DIE KLASSE BUFFER GUI CONFIG
     */
    vector<Datensatz> bufferVector[ANZAHL_ALLER];



	Datenaufbereitung();

	virtual ~Datenaufbereitung();

    void setup(Datenlogger *Datenlogptr);

    void liveAnforderungDaten(int ID);

    void stoppLiveAnforderungDaten(int ID);

    bool doConfig();

    void setOrdnernameConfigfile(QString ordnerNameConfigfile);

    void setPfadConfigfile(QString pfadConfigfile);

    void bodediagramm();
    void fft(int anzahl);
    void mittelwert();
    void ortskurve();

    void editBoundaries(int ID, QTime duration);
    
    void resetBoundaries();
    
    void getData(int ID);

    void getAllData(int ID);
    
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
    
    Datenlogger *datalog;

};
#endif // !defined(EA_86BA3343_9565_435f_A3A1_0F129309C661__INCLUDED_)
