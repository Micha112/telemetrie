#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Datenlogger;
class Datenverarbeitung;
class Datensatz;

#include <qwidget.h>
#include <qdebug.h>
#include <qwt_scale_engine.h>
#include <qlabel.h>
#include <plot.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <string>
#include <fstream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMouseEvent>
#include <QListWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QRadioButton>
#include <QToolButton>
#include <QPoint>
#include <QLine>
#include <QRect>
#include <QSize>
#include <QColor>
#include <QColorDialog>
#include <QLinearGradient>
#include <QBrush>
#include <QToolBar>
#include <qwt_plot_panner.h>
#include <QSlider>
#include <QListWidgetItem>
#include <QLabel>
#include <QPen>
#include <QLineEdit>
#include <QComboBox>
#include <QDesktopServices>
#include <QTimer>
#include <vector>
#include <list>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QMainWindow>
#include <QByteArray>
#include <QString>

#include <datenlogger.h>
#include <Datenverarbeitung.h>
#include <Datenaufbereitung.h>


using namespace std;

class Plot;

namespace Ui {
class MainWindow;
}

/**
 * In der Klasse MainWindow wird die Benutzeroberflaeche erstellt.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();

private slots:
    //////////////////////////////////////////
    void update234();
    ////////////////////////////////////////////
    void funktion_laden();
    void funktion_speichern();
    void funktion_neu();
    void funktion_einFenster();
    void funktion_zweiFenster();
    void funktion_messwerttabelleEinblenden();
    void funktion_messwerttabelleAusblenden();
    void funktion_projektordnerEinblenden();
    void funktion_projektordnerAusblenden();
    void funktion_ansichtWiederherstellen();
    void funktion_fahrerfunk();
    void funktion_hintergrundfarbeAendern();
    void funktion_okHintergrundfarbe();
    void funktion_abbrechenHintergrundfarbe();
    void funktion_plotVerschieben();
    void funktion_xAchseZoomen();
    void funktion_yAchseZoomen();
    void funktion_rechteckZoomen();
    void funktion_herausZoomen();
    void funktion_zoomZuruecksetzen();
    void funktion_zoomZuruecksetzenPlot1();
    void funktion_zoomZuruecksetzenPlot2();
    void funktion_maus();
    void funktion_okPloteigenschaftenPlot1();
    void funktion_okPloteigenschaftenPlot2();
    void funktion_abbrechenPloteigenschaften();
    void funktion_ploteigenschaftenPlot1(QModelIndex);
    void funktion_ploteigenschaftenPlot1(int);
    void funktion_ploteigenschaftenPlot2(QModelIndex);
    void funktion_ploteigenschaftenPlot2(int);
    void funktion_sucheMesswerteEinzelnPlot1(const QString &arg1);
    void funktion_sucheMesswertGruppiertPlot1(const QString &arg1);
    void funktion_sucheMesswerteEinzelnPlot2(const QString &arg1);
    void funktion_sucheMesswertGruppiertPlot2(const QString &arg1);
    void funktion_sucheAktuelleMessewertePlot1(const QString &arg1);
    void funktion_sucheAktuelleMessewertePlot2(const QString &arg1);
    void funktion_sucheoffeneProjekte(const QString &arg1);
    void funktion_sucheMesswerteMessdatengruppen(const QString &arg1);
    void funktion_aktuelleMesswertePlot1Angeklickt();
    void funktion_aktuelleMesswertePlot2Angeklickt();
    void funktion_tabWidgetPlot1Angeklickt();
    void funktion_tabWidgetPlot2Angeklickt();
    void funktion_messwertePlot1Hinzufuegen(QModelIndex);
    void funktion_messwertePlot2Hinzufuegen(QModelIndex);
    void funktion_messwertgruppePlot1Hinzufuegen(QModelIndex);
    void funktion_messwertgruppePlot2Hinzufuegen(QModelIndex);
    void funktion_einstellungen();
    void funktion_messwertZuGruppeHinzufuegen();
    void funktion_messwertZuGruppeHinzufuegen(QListWidgetItem*);
    void funktion_messwertVonGruppeEntfernen();
    void funktion_neueMesswertgruppeErstellen();
    void funktion_messwertgruppeEntfernen();
    void funktion_messwertgruppeNameAendern(const QString &arg1);
    void funktion_comboBoxMesswertgruppen();
    void funktion_okEinstellungen();
    void funktion_abbrechenEinstellungen();
    void funktion_hilfe();
    void funktion_mauskoordinatenAnzeigen();
    void funktion_plot1Plot2Synchronisieren();




private:
    Ui::MainWindow *ui;

    ///////////////////////////////////
    Datensatz *data;
    Datenlogger *Datalog;
    Datenverarbeitung *dataverarb;
    Datenaufbereitung *datenaufb;
    QTime timer234;
    ///////////////////////////////////

    void guiInitialisieren();
    void guiElementeEigenschaften();
    void layoutsErstellen();
    void menuBarErstellen();
    void toolBarErstellen();
    void signaleMitSlotsVerbinden();
    void messdatengruppenSpeichern();
    void messdatengruppenLaden();
    void messwertgruppenListWidgetErzeugen();

    Plot *d_plot1;
    Plot *d_plot2;
    double intervalLength;

    QVBoxLayout layout_gesamt;
    QVBoxLayout vLayout_projektordnerPlotsMesswerteBtnFahrerfunk;
    QVBoxLayout vLayout_ploteigenschaften;
    QVBoxLayout vLayout_messwerteEinzelnPlot1;
    QVBoxLayout vLayout_messwerteEinzelnPlot2;
    QVBoxLayout vLayout_messwerteGruppiertPlot1;
    QVBoxLayout vLayout_messwerteGruppiertPlot2;
    QVBoxLayout vLayout_messwerteAktuellPlot1;
    QVBoxLayout vLayout_messwerteAktuellPlot2;
    QVBoxLayout vLayout_offeneProjekte;
    QVBoxLayout vLayout_buttonsMesswertgruppen;
    QVBoxLayout vLayout_einstellungen;
    QVBoxLayout vLayout_hintergrundfarbe;

    QHBoxLayout hLayout_buttonsPloteigenschaften;
    QHBoxLayout hLayout_buttonsEinstellungen;
    QHBoxLayout hLayout_buttonsHintergrundfarbe;

    QGridLayout gLayout_linienart;
    QGridLayout gLayout_slider;
    QGridLayout gLayout_messwertgruppenBearbeiten;

    QSplitter splitter_plot1Plot2;
    QSplitter splitter_plot1MesswertePlot1;
    QSplitter splitter_plot2MesswertePlot2;
    QSplitter splitter_projektePlotsMesswerttabelle;

    QPushButton btn_fahrerfunk;
    QPushButton btn_okPloteigenschaften;
    QPushButton btn_abbrechenPloteigenschaften;
    QPushButton btn_messwertZuGruppeHinzufuegen;
    QPushButton btn_messwertVonGruppeEntfernen;
    QPushButton btn_neueMesswertgruppeErstellen;
    QPushButton btn_messwertgruppeEntfernen;
    QPushButton btn_okEinstellungen;
    QPushButton btn_abbrechenEinstellungen;
    QPushButton btn_okHintergrundfarbe;
    QPushButton btn_abbrechenHintergrundfarbe;

    QRadioButton radioBtn_durchgezogeneLinie;
    QRadioButton radioBtn_gestrichelteLinie;
    QRadioButton radioBtn_gepunkteteLinie;
    QRadioButton radioBtn_punktStrichLinie;
    QRadioButton radioBtn_punktPunktStrichLinie;

    QLabel label_linienfarbe;
    QLabel label_liniendicke;
    QLabel label_linienart;
    QLabel label_1;
    QLabel label_5;
    QLabel label_10;
    QLabel label_20;

    QLineEdit lineEdit_messwerteEinzelnPlot1;
    QLineEdit lineEdit_messwertGruppiertPlot1;
    QLineEdit lineEdit_messwerteEinzelnPlot2;
    QLineEdit lineEdit_messwertGruppiertPlot2;
    QLineEdit lineEdit_aktuelleMessewertePlot1;
    QLineEdit lineEdit_aktuelleMessewertePlot2;
    QLineEdit lineEdit_offeneProjekte;
    QLineEdit lineEdit_nameMesswertgruppe;
    QLineEdit lineEdit_messwerteEinzelnMessdatengruppen;

    QSlider slider_dickePlot;

    QToolBar toolBar_buttons;

    QComboBox comboBox_messwertgruppen;

    QWidget widget_plot1MesswertePlot1;
    QWidget widget_plot2MesswertePlot2;
    QWidget widget_btnFahrerfunktabWidgetMessdaten;
    QWidget widget_gesamt;
    QWidget widget_ploteigenschaften;
    QWidget widget_buttonsPloteigenschaften;
    QWidget widget_linienart;
    QWidget widget_slider;
    QWidget widget_messwerteEinzelnPlot1;
    QWidget widget_messwerteEinzelnPlot2;
    QWidget widget_messwerteGruppiertPlot1;
    QWidget widget_messwerteGruppiertPlot2;
    QWidget widget_messwerteAktuellPlot1;
    QWidget widget_messwerteAktuellPlot2;
    QWidget widget_offeneProjekte;
    QWidget widget_einstellungenAllgemein;
    QWidget widget_buttonsMesswertgruppen;
    QWidget widget_messwertgruppen;
    QWidget widget_buttonsEinstellungen;
    QWidget widget_einstellungen;
    QWidget widget_hilfe;
    QWidget widget_hintergrundfarbe;
    QWidget widget_buttonsHintergrundfarbe;

    QTabWidget tabWidget_messdatenPlot1;
    QTabWidget tabWidget_messdatenPlot2;
    QTabWidget tabWidget_einstellungen;

    QListWidget listWidget_messwerteEinzelnPlot1;
    QListWidget listWidget_messwertGruppiertPlot1;
    QListWidget listWidget_messwerteEinzelnPlot2;
    QListWidget listWidget_messwertGruppiertPlot2;
    QListWidget listWidget_aktuelleMesswertePlot1;
    QListWidget listWidget_aktuelleMesswertePlot2;
    QListWidget listWidget_offeneProjekte;
    QListWidget listWidget_messwertgruppen;
    QListWidget listWidget_messwerteEinzelnMessdatengruppen;

    QListWidgetItem *listWidgetItem;
    /**
     * @brief messdatengruppen
     * Das zweidimensionale QListWidgetItem-Array messdatengruppen enthaelt alle angelegten Messdatengruppen mit den dazugehoerigen Messdaten.
     * In der ersten Spalte stehen die Namen der Messdatengruppen. In der jeweiligen Zeile einer Messdatengruppe stehen dann die zugehoerigen Messwerte.
     */
    QListWidgetItem messdatengruppen[30][30];      //messdatengruppen[maxAnzahlMesswertgruppen][maxAnzahlElementeMesswergruppen]
    int maxAnzahlMesswertgruppen = 30;                //Klammerwert der ersten Klammer von listWidgetItemArray fuer Variable uebernehmen
    int maxAnzahlElementeMesswertgruppe = 30;         //Klammerwert der zweiten Klammer von listWidgetItemArray fuer Variable uebernehmen

    QMenu menu_datei;
    QMenu menu_tools;
    QMenu menu_anzeige;
    QMenu menu_anzahlFenster;
    QMenu menu_einstellungen;
    QMenu menu_zoomen;
    QMenu menu_hilfe;


    QAction action_neu;
    QAction action_laden;
    QAction action_speichern;
    QAction action_einFenster;
    QAction action_zweiFenster;
    QAction action_messwerttabelleEinblenden;
    QAction action_messwerttabelleAusblenden;
    QAction action_projektordnerEinblenden;
    QAction action_projektordnerAusblenden;
    QAction action_ansichtWiederherstellen;
    QAction action_hintergrundfarbeAendern;
    QAction action_stifteigenschaftenAendern;
    QAction action_xAchseHineinZoomen;
    QAction action_yAchseHineinZoomen;
    QAction action_rechteckZoomen;
    QAction action_herausZoomen;
    QAction action_zoomZuruecksetzen;
    QAction action_einstellungen;
    QAction action_maus;
    QAction action_plotVerschieben;
    QAction action_hilfe;
    QAction action_mauskoordinatenAnzeigen;
    QAction action_plot1Plot2Synchronisieren;

    QPoint positionMausAlt;
    QPoint positionMausAltFuerY;
    QPoint positionMausNeu;
    QPoint positionMausNeuFuerY;
    QPoint point_zwischenspeicher;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QColor hintergrundfarbe;
    QBrush brush_hintergrundfarbe;
    QPainter painter;
    QColorDialog *colorDialogPlot;
    QColorDialog *colorDialogHintergrundfarbe;
    QPen pen;

    QLine linie;

    QwtPlotPanner *plotPannerPlot1;
    QwtPlotPanner *plotPannerPlot2;

    QModelIndex *modelIndex;

    int positionItemPlot1Ploteigenschaften;
    int positionItemPlot2Ploteigenschaften;

    double xAxisMinPlot1;
    double xAxisMaxPlot1;
    double yAxisMinPlot1;
    double yAxisMaxPlot1;
    double xAxisMinPlot2;
    double xAxisMaxPlot2;
    double yAxisMinPlot2;
    double yAxisMaxPlot2;

    double xAxisMinNeuPlot1;
    double xAxisMaxNeuPlot1;
    double yAxisMinNeuPlot1;
    double yAxisMaxNeuPlot1;
    double xAxisMinNeuPlot2;
    double xAxisMaxNeuPlot2;
    double yAxisMinNeuPlot2;
    double yAxisMaxNeuPlot2;

    double xPosMausInPlot;
    double yPosMausInPlot;
    double xPosPlot;
    double yPosPlot;
    double xAxisValuePlot1;
    double xAxisValuePlot2;
    double yAxisValuePlot1;
    double yAxisValuePlot2;
    double deltaXMaus;
    double deltaYMaus;
    double xBreitePlot;
    double yBreitePlot;

    bool fahrerfunkStatus;
    bool einFensterAusgewaehlt;
    bool messwerttabelleEingeblendet;
    bool projektordnerEingeblendet;
    bool mausInnerhalbPlot1;
    bool mausInnerhalbPlot2;
    bool mauskoordinatenAnzeigen;

    QString qstring_text;
    QString qstring_suchtext;
    string text;

    QString namenMessdaten[100]; // Anzahl in Klammern = maximale Anzahl an Messdaten, die gezeichnet werden koennen
    int maxAnzahlMessdaten = 100; //maximale Anzahl an Messdaten anpassen, wenn mehr Messdaten geplotet werden sollen

    int zeile;
    int spalte;

    ofstream writefile;
    ifstream readfile;

    QTimer timer;
    QTimer timerDatenSchreiben;

    //QVector<int> vektorAktuellGeploteteMesswertePlot1;
    int aktuellGeploteteMesswertePlot1[100];
    int aktuellGeploteteMesswertePlot2[100];

    //////////////////////

    bool starttt = false;

    //////////////////////

};

#endif // MAINWINDOW_H
