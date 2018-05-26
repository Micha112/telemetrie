///////////////////////////////////////////////////////////
//  Datenlogger.cpp
//  Implementation of the Class Datenlogger
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#include "Datenlogger.h"

/**
 * @brief Datenlogger::Datenlogger
 * Konstruktor der Klasse Datenlogger
 * Setzt provisorisch alle Namen der im Array "fileDaten" enthaltenen QFiles auf "ERROR"
 */
Datenlogger::Datenlogger(){
    for(int i=0;i<ANZAHL_ALLER;i++)
    {
        fileDaten[i].setFileName("ERROR");
    }
}

/**
 * @brief Datenlogger::~Datenlogger
 * Destruktor der Klasse Datenlogger, hat noch keine bestimmte Funktion
 */
Datenlogger::~Datenlogger(){

}


/**
 * @brief Datenlogger::logfileErstellen
 * Speichert die Logfile am Ort "pfadDatensatz"->"ordnerNameDatensatz" ab
 * @param ID
 * @return
 * @attention Möglicherweise Probleme mit dem Zeitpunkt WANN die File geöffnet bzw geschlossen ist, unter anderem, da Sie nie wirklich geschlossen wird
 */
bool Datenlogger::logfileErstellen(int ID){
    QDir directory;
    if(ordnerNameDatensatz == "" || pfadDatensatz == "")
    {
        /**
         * @todo Meldung ueber Klassen hinweg an GUI das Pfad und Dateiname zum abspeichern benoetigt wird.
         */
        return false;
    }
    else
    {
        QString tempName = "DatenID";
        tempName.append(QString::number(ID));
        tempName.append(".txt");
        QString tempPath = pfadDatensatz;
        tempPath.append("/");
        directory.setCurrent(tempPath);
        directory.mkdir(ordnerNameDatensatz);
        tempPath.append(ordnerNameDatensatz);
        tempPath.append("/");
        directory.setCurrent(tempPath);
        fileDaten[ID].setFileName(tempName);
        if(!fileDaten[ID].open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
        {
            /**
             * @todo Meldung ueber Klassen hinweg an GUI das Datei nicht geoeffnet wurden konnte.
             */
        }
        return true;
    }
}


/**
 * @brief Datenlogger::liveAnforderungDaten
 * Greift auf ein Array zu, das so viele "Slots" wie IDs hat, und setzt 1 für "wird live benötigt"
 * @param ID
 */
void Datenlogger::liveAnforderungDaten(int ID)
{
    liveIDVector[ID] = 1;
}


/**
 * @brief Datenlogger::logfileSchreiben
 * Bekommt den Datenatz Frame und hängt eine passende Zeile an die Logfile an
 * Wert, Zeit und ID werden aus Frame entnommen und davor überprüft ob die Logfile vorhanden ist
 *  -> wenn nicht, logfileErstellen()
 * @param Frame
 * @return
 */
bool Datenlogger::logfileSchreiben(Datensatz Frame){

    QString tempString = "DatenID";
    tempString.append((QString)Frame.getID());

    if(!fileDaten[Frame.getID()].isOpen())
    {
        if(!logfileErstellen(Frame.getID()))
        {
            return false;
        }
    }
    out.setDevice(&fileDaten[Frame.getID()]);
    stringDatensatz.clear();
    stringDatensatz.append(QString::number(Frame.getID()));
    stringDatensatz.append("~");
    stringDatensatz.append(Frame.getZeit().toString("hh:mm:ss.zzz"));
    stringDatensatz.append("~");
    stringDatensatz.append(QString::number(Frame.getWert()));
    stringDatensatz.append("\n");
    out << stringDatensatz;

    return true;
}


/**
 * @brief Datenlogger::stoppLiveAnforderungDaten
 * Klasse Befehls Konfiguration Verarbeitung uebermittelt weiter die von der GUI
 * gewuenschten Daten die nicht mehr angezeigt werden sollen.
 * @param ID
 * @attention Villeicht Vectoren die besher live angefordert wurden aus Arbeistsspeichergründen löschen
 */
void Datenlogger::stoppLiveAnforderungDaten(int ID)
{
    liveIDVector[ID] = 0;
}

/**
 * @brief Datenlogger::istNeuer
 * Überprüft, ob der neue Satz wirklich neuer ist, als der Satz, den es gerade anschaut
 * TRUE, wenn er neuer ist
 * @param neuerSatz
 * @param alterSatz
 * @return
 */
bool Datenlogger::istNeuer(QString neuerSatz, QString alterSatz)
{
    QStringList Listalt = alterSatz.split("~",QString::SkipEmptyParts);
    QStringList Listneu = neuerSatz.split("~",QString::SkipEmptyParts);
    QTime alteZeit = QTime::fromString(Listalt[1],"hh:mm:ss.zzz");
    QTime neueZeit = QTime::fromString(Listneu[1],"hh:mm:ss.zzz");
    if(neueZeit >= alteZeit)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief Datenlogger::findeZeilenanfang
 * @param xteZeileDavor Bsp.: Wenn 1 -> Zeile drüber, Wenn 2 -> 2 Zeilen darüber
 * @param fileDaten QFile Array der einzelnen Logfiles
 * @param frameID   ID, in der aktuell gesucht werden soll
 * @return return die Position des Anfangs der gewünschten Zeile
 *
 */
qint64 Datenlogger::findeZeilenanfang(int xteZeileDavor, QFile fileDaten[], int frameID)
{
    char tempchar;
    qint64 fileEndePos = fileDaten[frameID].pos();
    qint64 tempPos = fileEndePos-1;
    fileDaten[frameID].seek(tempPos);
    for(int i=0; i<xteZeileDavor+2; i++)
    {
        while(fileDaten[frameID].getChar(&tempchar) && !(tempchar == '\n'))
        {
            tempPos = tempPos-1;
            fileDaten[frameID].seek(tempPos);
        }
        if(i<xteZeileDavor)
        {
            tempPos = tempPos-2;
            fileDaten[frameID].seek(tempPos);
        }
    }
    return fileDaten[frameID].pos();
}


/**
 * @brief Datenlogger::datenAnListeAnhaengen
 * Notwendig für das Anhängen und Sortieren der Daten an den Vector für "logfileLesen"
 * @param data
 * @return
 */
bool Datenlogger::datenAnListeAnhaengen(Datensatz data)
{
    unsigned int merker = 0;
    unsigned int tempListenLaenge = 0;
    tempListenLaenge = guiIDVector[data.getID()].size();
        for(unsigned int i = 0;i<tempListenLaenge;i++)
        {
            if(data.getZeit() >= guiIDVector[data.getID()].at(i).getZeit())
            {
                merker = i+1;
            }
        }
        guiIDVector[data.getID()].insert(guiIDVector[data.getID()].begin()+merker, data);
    return true;
}


/**
 * @brief Datenlogger::logfileLesen
 * Durchsuchen einer Bestimmten in ID festegelegten Logfile nach Daten in dem von
 * "zeitStart" bis "zeitStop" festgelegten Bereich.
 * Sortiert die ältesten an den Anfang des Vectors "guiIDVector" ([0] <- älteste)
 * @param ID
 * @param ZeitRaum
 * @param listeDatensatz
 * @return
 */
bool Datenlogger::logfileLesen(int ID, QTime zeitStart, QTime zeitStop){

    QTime zeit;
    float wert;
    QStringList List;
    QString tempString;

    ///////////////////Auskommentiert wegen Bug, er findet die Dateien nicht
    ///////////////////In Zukunft ALLE am Anfang direkt erstellen
    //fileDaten[ID].open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    if(!fileDaten[ID].isOpen())
    {
        if(!logfileErstellen(ID))
        {
            return false;
        }
    }

    QTextStream in (&fileDaten[ID]);
    fileDaten[ID].seek(0);
    do{
        tempString.clear();
        tempString = in.readLine();
        if(!tempString.isEmpty())
        {
            List = tempString.split("~",QString::SkipEmptyParts);
            zeit = QTime::fromString(List[1],"hh:mm:ss.zzz");
            tempString = List[2];// Diese und die zeile danach können für effektivität auch in die if() gesetzt werden
            wert = tempString.toFloat();
            if(zeit >= zeitStart && zeit <= zeitStop)
            {
                Datensatz tempDatensatz(ID,wert,zeit);
                if(!datenAnListeAnhaengen(tempDatensatz))
                {
                    return false;
                }
            }
        }
    } while(!tempString.isEmpty());
    return true;
}


/**
 * @brief Datenlogger::setOrdnernameDatensatz
 * Zum setzen des Ordnernamens (Bsp.: "Deutschland2018") von der GUI aus
 * @param dateinameDatensatz
 */
void Datenlogger::setOrdnernameDatensatz(QString dateinameDatensatz){
    this->ordnerNameDatensatz = dateinameDatensatz;
}


/**
 * @brief Datenlogger::setPfadDatensatz
 * Zum setzen des Pfades zum Ordner
 * @param pfadDatensatz
 */
void Datenlogger::setPfadDatensatz(QString pfadDatensatz)
{
    this->pfadDatensatz = pfadDatensatz;
}

/**
 * @brief Datenlogger::incomeHandler
 * Bekommt den Datensatz Frame und schreibt diesen auf jeden fall in die passende Logfile
 * Falls die ID Live gebraucht wird, wird dies aus dem Array "liveIDVector" entnommen
 *  und der Datensatz direkt an den guiIDVector, angehängt
 * @param Frame
 */
void Datenlogger::incomeHandler(Datensatz Frame)
{
    logfileSchreiben(Frame);
    for(int i=0; i<ANZAHL_ALLER; i++)
    {
        if(liveIDVector[i] == 1){
            datenAnListeAnhaengen(Frame);
        }
    }
}

/**
 * @brief Datenlogger::vectorEmpty
 * Überprüft lediglich ob das Array mit der ID aus "ID" leer ist
 * @param ID
 * @return
 */
bool Datenlogger::vectorEmpty(int ID)
{
    if (guiIDVector[ID].size() == 0)
    {
        return true;
    }
    return false;
}

/**
 * @brief Datenlogger::datenEntnehmen
 * Entnimmt dem Vector einen Datensatz und returnt diesen.
 * Falls das Array mit "ID" leer ist, returnt er einen Datensatz mit den Werten 0, 0 und der aktuellen zeit
 * Falls eine Überprüfung auf diesen "Fehler" stattfinden soll, muss das in der funktion geschehen, die
 *  diese Funktion aufruft
 * @param ID
 * @return
 * @attention Könnte Bug verursachen durch fehlenden return Wert
 */
Datensatz Datenlogger::datenEntnehmen(int ID)
{
    if(!guiIDVector[ID].empty()){
    tempsatzDatenEntnehmen = guiIDVector[ID].front();
    guiIDVector[ID].erase(guiIDVector[ID].begin());
    return tempsatzDatenEntnehmen;
    }
    //return tempsatz;
}
