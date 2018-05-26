///////////////////////////////////////////////////////////
//  Datenverarbeitung.cpp
//  Implementation of the Class Datenverarbeitung
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Alex Stenke
///////////////////////////////////////////////////////////

#include "Datenverarbeitung.h"




Datenverarbeitung::Datenverarbeitung(){
    //Um den Vector mit leeren Dummys zu befüllen, damit später an keiner Stelle mehr ein "push" gemacht werden muss
    fromConfig dummy;
    for(int i=0; i<=1000; i++){
        configVector.push_back(dummy);
    }
}


Datenverarbeitung::~Datenverarbeitung(){

}

/**
 * @brief Datenverarbeitung::FrameEntpacken
 * Bekommt einen Datensatz von "Daten Senden Empfangen" rein.
 * Erstellt aus dem QByteArray "datagram" und dem Zeitstempel die benötigten "normalen" Datensätze
 *  (je nach dem, wie viele Daten welcher Größe in dem QByteArray stecken)
 *  Dabei werden die IDs auch gleich anhand von der Konfigfile auf unsere eigenen eindeutigen IDs umgesetzt
 *  es wird der Vector "configVector" dadurch zur Hilfe gezogen
 * @param Frame
 * @attention NOCH NICHT FERTIG
 */
void Datenverarbeitung::FrameEntpacken(Datensatz Frame){
    tempDataVector.clear();
    pullOutID(Frame);
    pullOutData(Frame);
    createDatensaetze(Frame);
    while(!tempDataVector.empty())
    {
        datalog->incomeHandler(tempDataVector.back());
        tempDataVector.pop_back();
    }
}

/**
 * @brief Datenverarbeitung::setup
 * @param Datenlogptr
 * Benötigt diese Setupfunktion, um den income Handler des Datenloggers aufzurufen
 */
void Datenverarbeitung::setup(Datenlogger *Datenlogptr)
{
    datalog = Datenlogptr;
}

void Datenverarbeitung::pullOutID(Datensatz Frame)
{

}

void Datenverarbeitung::pullOutData(Datensatz Frame)
{

}

void Datenverarbeitung::createDatensaetze(Datensatz Frame)
{

}

/**
 * @brief doConfig
 * Diese Funktion liest die Logfile ein und speichert das Ausgelesene im Vector "configVector" ab
 */

bool Datenverarbeitung::doConfig()
{
    if(pfadConfigfile == "")
    {
        /**
         * @todo Meldung ueber Klassen hinweg an GUI das Pfad und Dateiname zum abspeichern benoetigt wird.
         */
        return false;
    }
    QString tempname = "Daten_verarbeiten_konfig";
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
    do{
        List.clear();
        tempString.clear();
        tempString = in.readLine();
        if(!tempString.isEmpty())
        {
            List = tempString.split("~",QString::SkipEmptyParts);
            if(!List.isEmpty())
            {
                int tempint = 0;
                for(int i = 1; i < List.length();)
                {
                    QString tempstringforbegin = List[0];
                    QString tempstringforint = List[i];
                    configVector.at(tempstringforbegin.toInt()).oldID[tempint].length = tempstringforint.toInt();
                    tempstringforint = List[++i];
                    configVector.at(tempstringforbegin.toInt()).oldID[tempint].newID = tempstringforint.toInt();
                    i++;
                    tempint++;
                }
            }
        }
    } while(!tempString.isEmpty());
    return true;

}

void Datenverarbeitung::setOrdnernameConfigfile(QString ordnerNameConfigfile)
{
    this->ordnerNameConfigfile = ordnerNameConfigfile;
}

void Datenverarbeitung::setPfadConfigfile(QString pfadConfigfile)
{
    this->pfadConfigfile = pfadConfigfile;
}
