///////////////////////////////////////////////////////////
//  Datenaufbereitung.cpp
//  Implementation of the Class Datenaufbereitung
//  Created on:      14-Dez-2017 12:09:17
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#include "Datenaufbereitung.h"




Datenaufbereitung::Datenaufbereitung(){
    resetBoundaries();
}


Datenaufbereitung::~Datenaufbereitung(){
    
}

/**
 * @brief Datenaufbereitung::setup
 * Hier Pointer auf die Objekte aus der übergeordneten Funktion übergeben, die von dieser Klasse benötigt werden
 */
void Datenaufbereitung::setup(Datenlogger *Datenlogptr)
{
    datalog = Datenlogptr;
}

/**
 * @brief Datenlogger::liveAnforderungDaten
 * Klasse "Befehls Konfiguration Verarbeitung" übermittelt weiter die von der GUI
 *  gewünschten Daten, die nicht mehr angezeigt werden sollen
 * @param ID
 */
void Datenaufbereitung::liveAnforderungDaten(int ID)
{
    liveIDVector[ID] = 1;
}

/**
 * @brief Datenlogger::stoppLiveAnforderungDaten
 * Klasse "Befehls Konfiguration Verarbeitung" übermittelt weiter die von der GUI
 *  gewünschten Daten, die nicht mehr angezeigt werden sollen
 * @param ID
 * @attention Villeicht Vectoren die besher live angefordert wurden aus Arbeistsspeichergründen löschen
 */
void Datenaufbereitung::stoppLiveAnforderungDaten(int ID)
{
    liveIDVector[ID] = 0;
}

/**
 * @brief Datenaufbereitung::doConfig
 * @return
 * Liest aus einer Configfile die Zuordnung von IDs zu Name Einheit
 * Speichert die Zuordnung in einem Array vom Typ "Datensatz" namens "configArray"
 */
bool Datenaufbereitung::doConfig()
{
    if(pfadConfigfile == "")
    {
        /**
         * @todo Meldung ueber Klassen hinweg an GUI das Pfad und Dateiname zum abspeichern benoetigt wird.
         */
        return false;
    }
    QString tempname = "Daten_aufbereiten_konfig";
    tempname.append(".txt");
    QString tempPath = pfadConfigfile;
    tempPath.append("/");
    tempPath.append(tempname);
    QFile Configfile(tempPath);
    if(!Configfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        /**
             * @todo Meldung ueber Klassen hinweg an GUI das Datei nicht geoeffnet wurden konnte.
             */
        return false;
    }
    QTextStream in (&Configfile);
    Configfile.seek(0);
    QString tempString;
    QStringList List;
    int tempint;
    QString tempnametemp, tempeinheit, tempstringforint;
    do{
        tempString.clear();
        tempString = in.readLine();
        if(!tempString.isEmpty())
        {
            List = tempString.split("~",QString::SkipEmptyParts);
            tempstringforint = List[0];
            tempint = tempstringforint.toInt();
            tempnametemp = List[1];
            tempeinheit = List[2];
            configArray[tempint].configDummy(tempint,tempnametemp,tempeinheit);
        }
    } while(!tempString.isEmpty());
    return true;
}

/**
 * @brief Datenaufbereitung::setOrdnernameConfigfile
 * @param ordnerNameConfigfile
 * Zum setzten des Ordnernamens
 */
void Datenaufbereitung::setOrdnernameConfigfile(QString ordnerNameConfigfile)
{
    this->ordnerNameConfigfile = ordnerNameConfigfile;
}

/**
 * @brief Datenaufbereitung::setPfadConfigfile
 * @param pfadConfigfile
 * Zum setzten des Pfades, in dem der übergeordnete Ordner liegt
 */
void Datenaufbereitung::setPfadConfigfile(QString pfadConfigfile)
{
    this->pfadConfigfile = pfadConfigfile;
}


/**
 * <ul>
 * <li>Die Funktion bodediagramm erstellt aus Messdaten eine Bodediagramm,
 * wahlweise nach Betrag und Phase getrennt.</li>
 * </ul>
 */
void Datenaufbereitung::bodediagramm(){

}


/**
 * <ul>
 * <li>Die Funktion fft wendet auf die Messdaten die Fouriertransformation an.
 * </li>
 * <li>Der Funktion muessen die Anzahl der zu transformierenden Werte ueber den
 * Parameter anzahl mitgeteilt werden. </li>
 * </ul>
 */
void Datenaufbereitung::fft(int anzahl){

}


/**
 * <ul>
 * <li>Die Funktion bildet den Mittelwert ueber die Messdaten. </li>
 * </ul>
 */
void Datenaufbereitung::mittelwert(){

}


/**
 * <ul>
 * <li>Die Funktion ortskurve zeichnet die Ortskurve der Messdaten.</li>
 * </ul>
 */
void Datenaufbereitung::ortskurve(){
    
}

/**
 * @brief Datenaufbereitung::editBoundaries
 * @param ID
 * @param duration
 * Bekommt die ID und die Länge der Zeit, wie lange die Datensätze in der Vergangenheit angezeigt werden sollen
 *  und speichert dies in einem Array ab, anhand dessen Ihalt entschieden wird, wie viele Pakete übersprungen werden
 * (overloadArray)
 * //Kurzzeitig festgelegt, dass 3000 Werte zur Anzeige reichen (Variable BOUNDARIELIMIT)
 *
 */
void Datenaufbereitung::editBoundaries(int ID, QTime duration)
{
    int seconds, data;
    seconds = duration.hour()*3600 + duration.minute()*60 + duration.second() + 1;
    data = seconds*50; //50 basieren auf einer Lograte von 20ms (50 pro Sekunde)
    data = data/BOUNDARIELIMIT; //Rest wird abgeschnitten, Genauigkeit nicht sooo wichtig
    overloadArray[ID] = data;
}

/**
 * @brief Datenaufbereitung::resetBoundaries
 * Zum zurücksetzen der Boundaries, um spätere Bugs zu verhindern, z.B. nach neu Laden der Boundaries
 */
void Datenaufbereitung::resetBoundaries()
{
    for(int i=0; i<ANZAHL_ALLER; i++)
    {
        overloadArray[i] = 1;
        overloadCounterArray[i] = 1;
    }   
}

/**
 * @brief Datenaufbereitung::getData
 * Muss getriggert werden, um Daten vom guiIDVector runter zu holen, und fängt schon mal an, diese aufzubereiten.
 * 
 */
void Datenaufbereitung::getData(int ID)
{
    if(overloadArray[ID] == overloadCounterArray[ID])
    {
        //Der Fall, in dem das Datenpaket weiter geschickt werden kann, und NICHT aussortiert wird
        overloadCounterArray[ID] == 1;
        bufferVector[ID].push_back(datalog->datenEntnehmen(ID));
    }
    else
    {
        //Der Fall, in dem das Datenpaket gelöscht werden kann
        overloadCounterArray[ID] += 1;
        datalog->datenEntnehmen(ID);
    }
}

/**
 * @brief Datenaufbereitung::getAllData
 * @param ID
 * Kopiert ganzen guivector auf ein mal in den buffervector
 */
void Datenaufbereitung::getAllData(int ID)
{
    bufferVector[ID].clear();
    bufferVector[ID] = datalog->guiIDVector[ID];
}
