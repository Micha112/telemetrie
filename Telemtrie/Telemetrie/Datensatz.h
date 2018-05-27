///////////////////////////////////////////////////////////
//  Datensatz.h
//  Implementation of the Class Datensatz
//  Created on:      14-Dez-2017 12:09:18
//  Original author: Becker
///////////////////////////////////////////////////////////

#if !defined(EA_FAFBB507_E1D4_45cd_8788_66C8D9718C37__INCLUDED_)
#define EA_FAFBB507_E1D4_45cd_8788_66C8D9718C37__INCLUDED_

#include <QString>
#include <QTime>
#include <QByteArray>


/**
 * @brief Standart Datensatz
 * 
 * Erzeugt Objekt eines Datensatzes welcher alle Parameter einer Information
 * enthaelt.
 */
class Datensatz
{

public:
    Datensatz(unsigned int ID, float Wert, QTime Zeit);
	Datensatz();
	~Datensatz();
	QString getEinheit();
	unsigned int getID();
	QString getNameMesswert();
	float getWert();
	QTime getZeit();
	bool getDatensatz(unsigned int ID, float Wert, QTime Zeit, QString NameMesswert, QString Einheit);
	bool getDatensatz(unsigned int& ID, float& Wert, QTime& Zeit, QString& NameMesswert, QString& Einheit);
    void configDummy(unsigned int ID, QString NameMesswert, QString Einheit);

private:
    /**
     * @brief Einheit
     * Einheit des Werts
     */
	QString Einheit;
    /**
     * @brief ID
     * Can ID von Steuergeraet
     */
	unsigned int ID;
    /**
     * @brief NameMesswert
     * Name des Messwerts anwelchem Ort er entstanden ist.
     */
	QString NameMesswert;
    /**
     * @brief Wert
     * Wert zu ID und Zeit
     */
	float Wert;
    /**
     * @brief Zeit
     * Zeitpunkt zudem der Wert ermittelt wurde + einmalige Latenzzeit bei
     * Synchronisierung
     */
	QTime Zeit;
    /**
     * @brief Datagram
     * Für den Empfang von "Daten Empfangen Senden" zu "Daten verarbeiten"
     */
    QByteArray Datagram;

	bool checkID(unsigned int ID, QString& NameMesswert, QString& Einheit);

};
#endif // !defined(EA_FAFBB507_E1D4_45cd_8788_66C8D9718C37__INCLUDED_)
