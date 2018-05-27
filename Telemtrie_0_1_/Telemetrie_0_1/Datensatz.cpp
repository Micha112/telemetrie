///////////////////////////////////////////////////////////
//  Datensatz.cpp
//  Implementation of the Class Datensatz
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Becker
///////////////////////////////////////////////////////////

#include "Datensatz.h"




/**
 * <ul>
 * 	<li>Erhaehlt ein Empfangenes Datenpaket muss Name des Messwertes sowie Einheit
 * aus Vergleichstabelle herausfinden</li>
 * ID darf NIE 0 sein
 * </ul>
 */
Datensatz::Datensatz(unsigned int ID, float Wert, QTime Zeit){
    QString tempNameMesswert = "";
    QString tempEinheit = "";

    if(checkID(ID,tempNameMesswert,tempEinheit)) //Wenn ID in Liste vorhanden dann Rueckgabe true
    {
        this->ID = ID;
        this->Wert = Wert;
        this->Zeit = Zeit;
        this->NameMesswert = tempNameMesswert;
        this->Einheit = tempEinheit;
    }
    else
    {
        QTime tempZeit;
        this->ID = 0;
        this->Wert = 0;
        this->Zeit = tempZeit;
    }
}


/**
 * <ul>
 * 	<li>Init werte Zeit = 0:0:0:0 ID = 0 Wert = 0 NameMesswert = '' Einheit =
 * ''</li>
 * </ul>
 */
Datensatz::Datensatz(){
    QTime time;
    this->ID = 0;
    this->Wert = 0;
    this->Einheit ="";
    this->NameMesswert = "";
    this->Zeit = time;
}


/**
 * <ul>
 * 	<li>loeschen des Objekts Datensatz</li>
 * </ul>
 */
Datensatz::~Datensatz(){

}


QString Datensatz::getEinheit(){
    QString temp = this->Einheit;
    return  temp;
}


unsigned int Datensatz::getID(){
    unsigned int temp = this->ID;
    return temp;
}


QString Datensatz::getNameMesswert(){
    QString temp = NameMesswert;
    return  temp;
}


float Datensatz::getWert(){
    float temp = this->Wert;
    return temp;
}


QTime Datensatz::getZeit(){

    QTime temp = this->Zeit;
    return  temp;
}


bool Datensatz::getDatensatz(unsigned int& ID, float& Wert, QTime& Zeit, QString& NameMesswert, QString& Einheit){
    QTime nullTime;
    ID = this->ID;
    Wert = this->Wert;
    Zeit = this->Zeit;
    NameMesswert = this->NameMesswert;
    Einheit = this->Einheit;
    if(ID != 0 && Zeit != nullTime)
    {
        return true;
    }
    return false;
}

void Datensatz::configDummy(unsigned int ID, QString NameMesswert, QString Einheit)
{
    this->ID = ID;
    this->NameMesswert = NameMesswert;
    this->Einheit = Einheit;
}



/**
 * Uebergabe der ID Rueckgabe der zugehoerigen Einheit und des zugehoerigen Namens
 * aus einr Textdatei
 * 
 * @todo File Einbinden und Durchsuchen !! Ueberlegen wenn Programm Installiert
 * wird, sodass dieses File mit in der Installationsdatei ist und relativ
 * Adressiert ist.
 */
bool Datensatz::checkID(unsigned int ID, QString& NameMesswert, QString& Einheit){
    if(ID == 0)
    {
        return false;
    }
    else
    {
        //File suchen und öffnen
        //Durchsuchen nach ID
        // NameMesswert sowie Einheit herrausfinden und in Variablen abspeichern
        //File schließen
        return true;
    }
	return false;
}






