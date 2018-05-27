#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    intervalLength = 10; // in Sekunden

    QTimer *tick = new QTimer(this);
    connect(tick,SIGNAL(timeout()),this,SLOT(update234()));
    tick->start(5);
    timer234.start();

    Datalog = new Datenlogger;
    Datalog->setOrdnernameDatensatz("Deutschland_2018");
    Datalog->setPfadDatensatz(QDir::currentPath());

    dataverarb = new Datenverarbeitung;
    dataverarb->setup(Datalog);
    dataverarb->setPfadConfigfile(QDir::currentPath());

    datenaufb = new Datenaufbereitung;
    datenaufb->setup(Datalog);
    datenaufb->setPfadConfigfile(QDir::currentPath());

    d_plot1 = new Plot( this );
    d_plot1->setXAxisValue(0,10);
    d_plot1->setYAxisValue(0,200);
    ///////////////////////////////////////////////////
    d_plot1->setup(datenaufb);
    ///////////////////////////////////////////////////

    d_plot2 = new Plot(this);
    d_plot2->setXAxisValue(0,10);
    d_plot2->setYAxisValue(0,200);
    ///////////////////////////////////////////////////
    //d_plot2->setup(dataverarb);
    ///////////////////////////////////////////////////

    plotPannerPlot1 = new QwtPlotPanner(d_plot1->canvas());
    plotPannerPlot2 = new QwtPlotPanner(d_plot2->canvas());

    colorDialogPlot = new QColorDialog(&widget_ploteigenschaften);
    colorDialogPlot->setWindowFlags(Qt::Widget);
    colorDialogPlot->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    colorDialogHintergrundfarbe = new QColorDialog(&widget_hintergrundfarbe);
    colorDialogHintergrundfarbe->setWindowFlags(Qt::Widget);
    colorDialogHintergrundfarbe->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);

    guiInitialisieren();
    funktion_maus();
}

MainWindow::~MainWindow()
{
//    delete ui;
//    delete d_plot1;
//    delete d_plot2;
}

void MainWindow::start()
{
    d_plot1->start();
}

/**
 * @brief MainWindow::update
 * ZUM DEBUGGEN
 */
void MainWindow::update234()
{
    if(starttt==true)
    {
        //Nimmt nur die Sekunden der aktuellen Zeit, d.h. für die einzelnen Sekundenwerte werden mehrere Y-Werte erzeugt -> suboptimal
//        QTime current = QTime::currentTime();
//        QTime input(0,0,current.second());
//        data = new Datensatz(10,rand()%10,input);
//        qDebug() << input;

        //Nimmt die aktuelle Zeit seit 00:00 Uhr in Sekunden -> ziemlich große Werte
//        QTime current = QTime::currentTime();
//        QTime input(current.hour(),current.minute(),current.second(),current.msec());
//        data = new Datensatz(10,rand()%10,input);
//        qDebug() << input;

        //Zählt vom Startpunkt der Anwendung aus, die Sekunden hoch -> sinnvoll
        QTime input(0,0,timer234.elapsed()/1000,timer234.elapsed()%1000);
        data = new Datensatz(10,rand()%10,input);
        qDebug() << timer234.elapsed();


        //data = new Datensatz(10,rand()%10,QTime::currentTime());
        Datalog->incomeHandler(*data);
        delete data;
        d_plot1->messdatenZeichnen(1);
        funktion_zoomZuruecksetzenPlot1();
        //qDebug() << QTime::currentTime();
    }

    if(!Datalog->vectorEmpty(10))
    {
        datenaufb->getData(10);
    }
}

/**
 * @brief MainWindow::guiInitialisieren
 * Alle Funktionen, die zum Initialisieren der GUI benoetigt werden, werden aufgerufen.
 * Wichtige Statusvariablen werden mit ihrem Standardwert initialisiert.
 */
void MainWindow::guiInitialisieren()
{
    for(int i=0;i<26;i++)
    {
        namenMessdaten[i] = (i+97);
        listWidget_messwerteEinzelnPlot1.addItem(namenMessdaten[i]);
    }

    fahrerfunkStatus = false;
    einFensterAusgewaehlt = true;
    messwerttabelleEingeblendet = true;
    projektordnerEingeblendet = true;
    mausInnerhalbPlot1 = false;
    mausInnerhalbPlot2 = false;
    mauskoordinatenAnzeigen = true;

    guiElementeEigenschaften();
    layoutsErstellen();
    menuBarErstellen();
    toolBarErstellen();
    signaleMitSlotsVerbinden();
    messwertgruppenListWidgetErzeugen();



//    listWidget_messwerteEinzelnPlot1.addItem("a");
//    listWidget_messwerteEinzelnPlot1.addItem("b");
//    listWidget_messwerteEinzelnPlot1.addItem("c");
//    listWidget_messwerteEinzelnPlot1.addItem("d");
//    listWidget_messwerteEinzelnPlot1.addItem("e");
//    listWidget_messwerteEinzelnPlot1.addItem("f");
//    listWidget_messwerteEinzelnPlot1.addItem("g");
//    listWidget_messwerteEinzelnPlot1.addItem("h");
//    listWidget_messwerteEinzelnPlot1.addItem("i");
//    listWidget_messwerteEinzelnPlot1.addItem("j");
//    listWidget_messwerteEinzelnPlot1.addItem("k");
//    listWidget_messwerteEinzelnPlot1.addItem("l");
//    listWidget_messwerteEinzelnPlot1.addItem("m");
//    listWidget_messwerteEinzelnPlot1.addItem("n");
//    listWidget_messwerteEinzelnPlot1.addItem("o");
//    listWidget_messwerteEinzelnPlot1.addItem("p");
//    listWidget_messwerteEinzelnPlot1.addItem("q");
//    listWidget_messwerteEinzelnPlot1.addItem("r");
//    listWidget_messwerteEinzelnPlot1.addItem("s");
//    listWidget_messwerteEinzelnPlot1.addItem("t");
//    listWidget_messwerteEinzelnPlot1.addItem("u");
//    listWidget_messwerteEinzelnPlot1.addItem("v");
//    listWidget_messwerteEinzelnPlot1.addItem("w");
//    listWidget_messwerteEinzelnPlot1.addItem("x");
//    listWidget_messwerteEinzelnPlot1.addItem("y");
//    listWidget_messwerteEinzelnPlot1.addItem("z");




    for(int i = 0; i < listWidget_messwerteEinzelnPlot1.count(); i++)
    {
        listWidget_messwerteEinzelnMessdatengruppen.addItem(listWidget_messwerteEinzelnPlot1.item(i)->text());
        listWidget_messwerteEinzelnPlot2.addItem(listWidget_messwerteEinzelnPlot1.item(i)->text());
    }

    listWidget_aktuelleMesswertePlot1.installEventFilter(this);

}

/**
 * @brief MainWindow::guiElementeEigenschaften
 * Hier werden die geometrischen Groessen, die Namen und die Icons der GUI-Elemente festgelegt.
 */
void MainWindow::guiElementeEigenschaften()
{

    tabWidget_messdatenPlot1.setMaximumWidth(300);
    tabWidget_messdatenPlot2.setMaximumWidth(300);

    listWidget_offeneProjekte.setMaximumHeight(250);

    widget_ploteigenschaften.setWindowTitle("Ploteigenschaften");
    widget_ploteigenschaften.setWindowIcon(QIcon(":bilder/Bilder/stifteigenschaften.png"));

    btn_okPloteigenschaften.setText("OK");
    btn_okPloteigenschaften.setMaximumWidth(120);
    btn_abbrechenPloteigenschaften.setText("Abbrechen");
    btn_abbrechenPloteigenschaften.setMaximumWidth(120);

    slider_dickePlot.setOrientation(Qt::Horizontal);
    slider_dickePlot.setMinimum(1);
    slider_dickePlot.setMaximum(20);

    btn_fahrerfunk.setStyleSheet("background-color: red; color: white; font-size: 10pt; font: bold");
    btn_fahrerfunk.setToolTip("Fahrerfunk aktivieren");
    btn_fahrerfunk.setText("Fahrerfunk");
    btn_fahrerfunk.setMaximumWidth(120);

    menu_datei.setTitle("Datei");
    menu_tools.setTitle("Tools");
    menu_zoomen.setTitle("Zoom");
    menu_anzeige.setTitle("Anzeige");
    menu_anzahlFenster.setTitle("Anzahl Fenster");
    menu_einstellungen.setTitle("Einstellungen");
    menu_hilfe.setTitle("Hilfe");
    action_xAchseHineinZoomen.setText("x-Zoom");
    action_yAchseHineinZoomen.setText("y-Zoom");
    action_rechteckZoomen.setText("Rechteck-Zoom");
    action_herausZoomen.setText("Herauszoomen");
    action_zoomZuruecksetzen.setText("Zoom zurücksetzen");
    action_einFenster.setText("1");
    action_laden.setText("Laden");
    action_messwerttabelleAusblenden.setText("Messwerttabelle ausblenden");
    action_messwerttabelleEinblenden.setText("Messwerttabelle einblenden");
    action_neu.setText("Neu");
    action_projektordnerAusblenden.setText("Projektordner ausblenden");
    action_projektordnerEinblenden.setText("Projektordner einblenden");
    action_speichern.setText("Speichern");
    action_zweiFenster.setText("2 (Fenster teilen)");
    action_ansichtWiederherstellen.setText("Ansicht wiederherstellen");
    action_hintergrundfarbeAendern.setText("Hintergrundfarbe");
    action_einstellungen.setText("Einstellungen");
    action_maus.setText("Maus");
    action_plotVerschieben.setText("Verschieben");
    action_hilfe.setText("Hilfe");
    action_mauskoordinatenAnzeigen.setText("Zeige Koordinaten");
    action_plot1Plot2Synchronisieren.setText("Plot 1 und 2 synchronisieren");

    action_xAchseHineinZoomen.setIcon(QIcon(":bilder/Bilder/xZoomen.png"));
    action_yAchseHineinZoomen.setIcon(QIcon(":bilder/Bilder/yZoomen.png"));
    action_rechteckZoomen.setIcon(QIcon(":bilder/Bilder/rechteckZoomen.png"));
    action_herausZoomen.setIcon(QIcon(":bilder/Bilder/zoomMinus.png"));
    action_zoomZuruecksetzen.setIcon(QIcon(":bilder/Bilder/zoomZuruecksetzen"));
    action_laden.setIcon(QIcon(":bilder/Bilder/oeffnen.png"));
    action_speichern.setIcon(QIcon(":bilder/Bilder/speichern.png"));
    action_neu.setIcon(QIcon(":bilder/Bilder/neu.png"));
    action_einstellungen.setIcon(QIcon(":bilder/Bilder/einstellungen.png"));
    action_hintergrundfarbeAendern.setIcon(QIcon(":bilder/Bilder/hintergrundfarbe.png"));
    action_maus.setIcon(QIcon(":bilder/Bilder/maus.png"));
    action_plotVerschieben.setIcon(QIcon(":bilder/Bilder/plotVerschieben.png"));
    action_einstellungen.setIcon(QIcon(":bilder/Bilder/einstellungen.png"));
    menu_zoomen.setIcon(QIcon(":bilder/Bilder/zoomPlus.png"));
    action_hilfe.setIcon(QIcon(":bilder/Bilder/hilfe.png"));
    action_plot1Plot2Synchronisieren.setIcon(QIcon(":bilder/Bilder/plotsVerbinden.png"));

    action_xAchseHineinZoomen.setCheckable(true);
    action_yAchseHineinZoomen.setCheckable(true);
    action_rechteckZoomen.setCheckable(true);
    action_maus.setCheckable(true);
    action_plotVerschieben.setCheckable(true);
    action_herausZoomen.setCheckable(true);
    action_zoomZuruecksetzen.setCheckable(true);
    action_mauskoordinatenAnzeigen.setCheckable(true);
    action_mauskoordinatenAnzeigen.setChecked(true);
    action_plot1Plot2Synchronisieren.setCheckable(true);

    radioBtn_durchgezogeneLinie.setText("________________");
    radioBtn_gepunkteteLinie.setText(". . . . . . . . . . . .");
    radioBtn_gestrichelteLinie.setText("- - - - - - - - - - -");
    radioBtn_punktPunktStrichLinie.setText(". . _ . . _ . . _ . . ");
    radioBtn_punktStrichLinie.setText(". _ . _ . _ . _ . _ . _");
    label_linienart.setText("Linienart");
    label_linienart.setStyleSheet("font-size: 10pt; text-decoration: underline; font: bold");
    label_liniendicke.setText("Liniendicke");
    label_liniendicke.setStyleSheet("font-size: 10pt; text-decoration: underline; font: bold");
    label_linienfarbe.setText("Linienfarbe");
    label_linienfarbe.setStyleSheet("font-size: 10pt; text-decoration: underline; font: bold");
    label_1.setText("1");
    label_5.setText("5");
    label_10.setText("10");
    label_20.setText("20");

    btn_okEinstellungen.setText("OK");
    btn_okEinstellungen.setMaximumWidth(120);
    btn_abbrechenEinstellungen.setText("Abbrechen");
    btn_abbrechenEinstellungen.setMaximumWidth(120);

    btn_okHintergrundfarbe.setText("OK");
    btn_okHintergrundfarbe.setMaximumWidth(120);
    btn_abbrechenHintergrundfarbe.setText("Abbrechen");
    btn_abbrechenHintergrundfarbe.setMaximumWidth(120);

    btn_messwertZuGruppeHinzufuegen.setText(">>");
    btn_messwertZuGruppeHinzufuegen.setToolTip("Messwert zu Gruppe hinzufügen");
    btn_messwertVonGruppeEntfernen.setText("<<");
    btn_messwertVonGruppeEntfernen.setToolTip("Messwert von Gruppe entfernen");
    btn_neueMesswertgruppeErstellen.setText("+");
    btn_neueMesswertgruppeErstellen.setMaximumWidth(30);
    btn_neueMesswertgruppeErstellen.setToolTip("neue Messwertgruppe erstellen");
    btn_messwertgruppeEntfernen.setText("x");
    btn_messwertgruppeEntfernen.setMaximumWidth(30);
    btn_messwertgruppeEntfernen.setToolTip("Messwertgruppe entfernen");

    widget_einstellungen.setWindowTitle("Einstellungen");
    widget_einstellungen.setWindowIcon(QIcon(":bilder/Bilder/einstellungen.png"));
    widget_einstellungen.setGeometry(200,100,1200,800);

    widget_hintergrundfarbe.setWindowTitle("Hintergrundfarbe");
    widget_hintergrundfarbe.setWindowIcon(QIcon(":bilder/Bilder/hintergrundfarbe.png"));


    d_plot1->setMinimumSize(50,50);
    d_plot2->setMinimumSize(50,50);
    splitter_plot2MesswertePlot2.setVisible(false);

    action_messwerttabelleEinblenden.setEnabled(false);
    action_projektordnerEinblenden.setEnabled(false);

    lineEdit_offeneProjekte.setToolTip("offene Projekte durchsuchen");
    lineEdit_aktuelleMessewertePlot1.setToolTip("aktuelle Messwerte Plot 1durchsuchen");
    lineEdit_aktuelleMessewertePlot2.setToolTip("aktuelle Messwerte Plot 2 durchsuchen");
    lineEdit_messwerteEinzelnPlot1.setToolTip("Messdaten durchsuchen");
    lineEdit_messwerteEinzelnPlot2.setToolTip("Messdaten durchsuchen");
    lineEdit_messwertGruppiertPlot1.setToolTip("Messdatengruppen durchsuchen");
    lineEdit_messwertGruppiertPlot2.setToolTip("Messdatengruppen durchsuchen");
    lineEdit_nameMesswertgruppe.setToolTip("Name Messwertgruppe ändern");
    lineEdit_messwerteEinzelnMessdatengruppen.setToolTip("Messdaten durchsuchen");
    btn_abbrechenEinstellungen.setToolTip("Beenden, ohne Einstellungen zu übernehmen");
    btn_okEinstellungen.setToolTip("Beenden und Einstellungen übernehmen");
    btn_abbrechenHintergrundfarbe.setToolTip("Beenden, ohne Hintergrundfarbe zu übernehmen");
    btn_okHintergrundfarbe.setToolTip("Beenden und Hintergrundfarbe übernehmen");
    btn_okPloteigenschaften.setToolTip("Beenden, ohne Ploteigenschaften zu übernehmen");
    btn_abbrechenPloteigenschaften.setToolTip("Beenden und Ploteigenschaften übernehmen");
}

/**
 * @brief MainWindow::layoutsErstellen
 * Hier werden die Layouts erzeugt, die fuer die Oberflaeche gebraucht werden.
 */
void MainWindow::layoutsErstellen()
{
    tabWidget_messdatenPlot1.addTab(&widget_messwerteAktuellPlot1,"aktuelle Messdaten");
    tabWidget_messdatenPlot1.addTab(&widget_messwerteEinzelnPlot1,"Messdaten");
    tabWidget_messdatenPlot1.addTab(&widget_messwerteGruppiertPlot1,"Messwertgruppen");

    tabWidget_messdatenPlot2.addTab(&widget_messwerteAktuellPlot2,"aktuelle Messdaten");
    tabWidget_messdatenPlot2.addTab(&widget_messwerteEinzelnPlot2,"Messdaten");
    tabWidget_messdatenPlot2.addTab(&widget_messwerteGruppiertPlot2,"Messwertgruppen");

    vLayout_messwerteAktuellPlot1.addWidget(&lineEdit_aktuelleMessewertePlot1);
    vLayout_messwerteAktuellPlot1.addWidget(&listWidget_aktuelleMesswertePlot1);
    widget_messwerteAktuellPlot1.setLayout(&vLayout_messwerteAktuellPlot1);

    vLayout_messwerteAktuellPlot2.addWidget(&lineEdit_aktuelleMessewertePlot2);
    vLayout_messwerteAktuellPlot2.addWidget(&listWidget_aktuelleMesswertePlot2);
    widget_messwerteAktuellPlot2.setLayout(&vLayout_messwerteAktuellPlot2);

    vLayout_messwerteEinzelnPlot1.addWidget(&lineEdit_messwerteEinzelnPlot1);
    vLayout_messwerteEinzelnPlot1.addWidget(&listWidget_messwerteEinzelnPlot1);
    widget_messwerteEinzelnPlot1.setLayout(&vLayout_messwerteEinzelnPlot1);

    vLayout_messwerteEinzelnPlot2.addWidget(&lineEdit_messwerteEinzelnPlot2);
    vLayout_messwerteEinzelnPlot2.addWidget(&listWidget_messwerteEinzelnPlot2);
    widget_messwerteEinzelnPlot2.setLayout(&vLayout_messwerteEinzelnPlot2);

    vLayout_messwerteGruppiertPlot1.addWidget(&lineEdit_messwertGruppiertPlot1);
    vLayout_messwerteGruppiertPlot1.addWidget(&listWidget_messwertGruppiertPlot1);
    widget_messwerteGruppiertPlot1.setLayout(&vLayout_messwerteGruppiertPlot1);

    vLayout_messwerteGruppiertPlot2.addWidget(&lineEdit_messwertGruppiertPlot2);
    vLayout_messwerteGruppiertPlot2.addWidget(&listWidget_messwertGruppiertPlot2);
    widget_messwerteGruppiertPlot2.setLayout(&vLayout_messwerteGruppiertPlot2);

    vLayout_offeneProjekte.addWidget(&lineEdit_offeneProjekte);
    vLayout_offeneProjekte.addWidget(&listWidget_offeneProjekte);
    vLayout_offeneProjekte.addStretch(1);
    widget_offeneProjekte.setLayout(&vLayout_offeneProjekte);

    splitter_plot1MesswertePlot1.addWidget(d_plot1);
    splitter_plot1MesswertePlot1.addWidget(&tabWidget_messdatenPlot1);

    splitter_plot2MesswertePlot2.addWidget(d_plot2);
    splitter_plot2MesswertePlot2.addWidget(&tabWidget_messdatenPlot2);

    splitter_plot1Plot2.setOrientation(Qt::Vertical);
    splitter_plot1Plot2.addWidget(&splitter_plot1MesswertePlot1);
    splitter_plot1Plot2.addWidget(&splitter_plot2MesswertePlot2);

    splitter_projektePlotsMesswerttabelle.setOrientation(Qt::Horizontal);
    splitter_projektePlotsMesswerttabelle.addWidget(&widget_offeneProjekte);
    splitter_projektePlotsMesswerttabelle.addWidget(&splitter_plot1Plot2);
    splitter_projektePlotsMesswerttabelle.setStretchFactor(1,1);

    vLayout_projektordnerPlotsMesswerteBtnFahrerfunk.addWidget(&splitter_projektePlotsMesswerttabelle);
    widget_gesamt.setLayout(&vLayout_projektordnerPlotsMesswerteBtnFahrerfunk);
    layout_gesamt.addWidget(&widget_gesamt);

    hLayout_buttonsPloteigenschaften.addWidget(&btn_okPloteigenschaften);
    hLayout_buttonsPloteigenschaften.addWidget(&btn_abbrechenPloteigenschaften);
    widget_buttonsPloteigenschaften.setLayout(&hLayout_buttonsPloteigenschaften);

    gLayout_slider.addWidget(&slider_dickePlot,0,0,1,20);
    gLayout_slider.addWidget(&label_1,1,0,1,1);
    gLayout_slider.addWidget(&label_5,1,4,1,1);
    gLayout_slider.addWidget(&label_10,1,9,1,1);
    gLayout_slider.addWidget(&label_20,1,19,1,1);
    widget_slider.setLayout(&gLayout_slider);

    vLayout_ploteigenschaften.addWidget(&label_linienfarbe);
    vLayout_ploteigenschaften.addWidget(colorDialogPlot);
    vLayout_ploteigenschaften.addSpacing(30);
    vLayout_ploteigenschaften.addWidget(&label_liniendicke);
    vLayout_ploteigenschaften.addWidget(&widget_slider);
    vLayout_ploteigenschaften.addSpacing(30);
    vLayout_ploteigenschaften.addWidget(&label_linienart);
    vLayout_ploteigenschaften.addWidget(&widget_linienart);
    vLayout_ploteigenschaften.addWidget(&widget_buttonsPloteigenschaften);
    widget_ploteigenschaften.setLayout(&vLayout_ploteigenschaften);


    gLayout_linienart.addWidget(&radioBtn_durchgezogeneLinie,0,0);
    gLayout_linienart.addWidget(&radioBtn_gestrichelteLinie,0,1);
    gLayout_linienart.addWidget(&radioBtn_gepunkteteLinie,0,2);
    gLayout_linienart.addWidget(&radioBtn_punktStrichLinie,1,0);
    gLayout_linienart.addWidget(&radioBtn_punktPunktStrichLinie,1,1);
    widget_linienart.setLayout(&gLayout_linienart);



    hLayout_buttonsEinstellungen.addWidget(&btn_okEinstellungen);
    hLayout_buttonsEinstellungen.addWidget(&btn_abbrechenEinstellungen);
    widget_buttonsEinstellungen.setLayout(&hLayout_buttonsEinstellungen);

    hLayout_buttonsHintergrundfarbe.addWidget(&btn_okHintergrundfarbe);
    hLayout_buttonsHintergrundfarbe.addWidget(&btn_abbrechenHintergrundfarbe);
    widget_buttonsHintergrundfarbe.setLayout(&hLayout_buttonsHintergrundfarbe);

    vLayout_hintergrundfarbe.addWidget(colorDialogHintergrundfarbe);
    vLayout_hintergrundfarbe.addWidget(&widget_buttonsHintergrundfarbe);
    widget_hintergrundfarbe.setLayout(&vLayout_hintergrundfarbe);


    gLayout_messwertgruppenBearbeiten.addWidget(&listWidget_messwerteEinzelnMessdatengruppen,2,0);
    gLayout_messwertgruppenBearbeiten.addWidget(&lineEdit_messwerteEinzelnMessdatengruppen,1,0);
    gLayout_messwertgruppenBearbeiten.addWidget(&comboBox_messwertgruppen,0,2);
    gLayout_messwertgruppenBearbeiten.addWidget(&listWidget_messwertgruppen,2,2);
    gLayout_messwertgruppenBearbeiten.addWidget(&widget_buttonsMesswertgruppen,2,1);
    gLayout_messwertgruppenBearbeiten.addWidget(&btn_neueMesswertgruppeErstellen,0,3);
    gLayout_messwertgruppenBearbeiten.addWidget(&btn_messwertgruppeEntfernen,1,3);
    gLayout_messwertgruppenBearbeiten.addWidget(&lineEdit_nameMesswertgruppe,1,2);
    widget_messwertgruppen.setLayout(&gLayout_messwertgruppenBearbeiten);

    tabWidget_einstellungen.addTab(&widget_einstellungenAllgemein,"Allgemein");
    tabWidget_einstellungen.addTab(&widget_messwertgruppen,"Messwertgruppen");



    vLayout_einstellungen.addWidget(&tabWidget_einstellungen);
    vLayout_einstellungen.addWidget(&widget_buttonsEinstellungen);
    widget_einstellungen.setLayout(&vLayout_einstellungen);


    vLayout_buttonsMesswertgruppen.addWidget(&btn_messwertZuGruppeHinzufuegen);
    vLayout_buttonsMesswertgruppen.addWidget(&btn_messwertVonGruppeEntfernen);
    widget_buttonsMesswertgruppen.setLayout(&vLayout_buttonsMesswertgruppen);

    ui->centralWidget->setLayout(&layout_gesamt);
}

/**
 * @brief MainWindow::menuBarErstellen
 * Hier wird die Menuebar erzeugt.
 */
void MainWindow::menuBarErstellen()
{
    menuBar()->addMenu(&menu_datei);
    menu_datei.addAction(&action_laden);
    menu_datei.addAction(&action_speichern);
    menu_datei.addAction(&action_neu);

    action_laden.setShortcut(tr("CTRL+o"));
    action_neu.setShortcut(tr("CTRL+n"));
    action_speichern.setShortcut(tr("CTRL+s"));

    menuBar()->addMenu(&menu_tools);
    menu_tools.addAction(&action_plot1Plot2Synchronisieren);
    menu_tools.addMenu(&menu_zoomen);
    menu_tools.addAction(&action_maus);
    menu_tools.addAction(&action_plotVerschieben);
    menu_zoomen.addAction(&action_xAchseHineinZoomen);
    menu_zoomen.addAction(&action_yAchseHineinZoomen);
    menu_zoomen.addAction(&action_rechteckZoomen);
    menu_zoomen.addAction(&action_zoomZuruecksetzen);
    menu_tools.addAction(&action_plotVerschieben);

    menuBar()->addMenu(&menu_anzeige);
    menu_anzahlFenster.addAction(&action_einFenster);
    menu_anzahlFenster.addAction(&action_zweiFenster);
    menu_anzeige.addMenu(&menu_anzahlFenster);
    menu_anzeige.addSeparator();
    menu_anzeige.addAction(&action_messwerttabelleEinblenden);
    menu_anzeige.addAction(&action_messwerttabelleAusblenden);
    menu_anzeige.addSeparator();
    menu_anzeige.addAction(&action_projektordnerEinblenden);
    menu_anzeige.addAction(&action_projektordnerAusblenden);
    menu_anzeige.addSeparator();
    menu_anzeige.addAction(&action_mauskoordinatenAnzeigen);
    menu_anzeige.addSeparator();
    menu_anzeige.addAction(&action_ansichtWiederherstellen);

    menuBar()->addMenu(&menu_einstellungen);
    menu_einstellungen.addAction(&action_hintergrundfarbeAendern);
    menu_einstellungen.addAction(&action_einstellungen);

    menuBar()->addMenu(&menu_hilfe);
    menu_hilfe.addAction(&action_hilfe);
    action_hilfe.setShortcut(tr("F1"));
}

/**
 * @brief MainWindow::toolBarErstellen
 * Hier wird die Toolbar erstellt.
 */
void MainWindow::toolBarErstellen()
{
    toolBar_buttons.addWidget(&btn_fahrerfunk);
    toolBar_buttons.addSeparator();
    toolBar_buttons.addAction(&action_neu);
    toolBar_buttons.addAction(&action_laden);
    toolBar_buttons.addAction(&action_speichern);
    toolBar_buttons.addSeparator();
    toolBar_buttons.addAction(&action_maus);
    toolBar_buttons.addAction(&action_plot1Plot2Synchronisieren);
    toolBar_buttons.addAction(&action_plotVerschieben);
    toolBar_buttons.addSeparator();
    toolBar_buttons.addAction(&action_xAchseHineinZoomen);
    toolBar_buttons.addAction(&action_yAchseHineinZoomen);
    toolBar_buttons.addAction(&action_rechteckZoomen);
    toolBar_buttons.addAction(&action_herausZoomen);
    toolBar_buttons.addAction(&action_zoomZuruecksetzen);
    toolBar_buttons.addSeparator();
    toolBar_buttons.addAction(&action_hintergrundfarbeAendern);
    toolBar_buttons.addAction(&action_einstellungen);

    addToolBar(&toolBar_buttons);
}

/**
 * @brief MainWindow::signaleMitSlotsVerbinden
 * Hier werden die Signale der einzelnen GUI-Elemente mit den jeweiligen Slots verbunden.
 */
void MainWindow::signaleMitSlotsVerbinden()
{
    connect(&action_ansichtWiederherstellen,SIGNAL(triggered()),this,SLOT(funktion_ansichtWiederherstellen()));
    connect(&action_einFenster,SIGNAL(triggered()),this,SLOT(funktion_einFenster()));
    connect(&action_laden,SIGNAL(triggered()),this,SLOT(funktion_laden()));
    connect(&action_messwerttabelleAusblenden,SIGNAL(triggered()),this,SLOT(funktion_messwerttabelleAusblenden()));
    connect(&action_messwerttabelleEinblenden,SIGNAL(triggered()),this,SLOT(funktion_messwerttabelleEinblenden()));
    connect(&action_neu,SIGNAL(triggered()),this,SLOT(funktion_neu()));
    connect(&action_projektordnerAusblenden,SIGNAL(triggered()),this,SLOT(funktion_projektordnerAusblenden()));
    connect(&action_projektordnerEinblenden,SIGNAL(triggered()),this,SLOT(funktion_projektordnerEinblenden()));
    connect(&action_speichern,SIGNAL(triggered()),this,SLOT(funktion_speichern()));
    connect(&action_zweiFenster,SIGNAL(triggered()),this,SLOT(funktion_zweiFenster()));
    connect(&btn_fahrerfunk,SIGNAL(clicked()),this,SLOT(funktion_fahrerfunk()));
    connect(&action_hintergrundfarbeAendern,SIGNAL(triggered()),this,SLOT(funktion_hintergrundfarbeAendern()));
    connect(&action_plotVerschieben,SIGNAL(triggered()),this,SLOT(funktion_plotVerschieben()));
    connect(&action_xAchseHineinZoomen,SIGNAL(triggered()),this,SLOT(funktion_xAchseZoomen()));
    connect(&action_yAchseHineinZoomen,SIGNAL(triggered()),this,SLOT(funktion_yAchseZoomen()));
    connect(&action_rechteckZoomen,SIGNAL(triggered()),this,SLOT(funktion_rechteckZoomen()));
    connect(&action_herausZoomen,SIGNAL(triggered()),this,SLOT(funktion_herausZoomen()));
    connect(&action_zoomZuruecksetzen,SIGNAL(triggered()),this,SLOT(funktion_zoomZuruecksetzen()));
    connect(&action_maus,SIGNAL(triggered()),this,SLOT(funktion_maus()));
    connect(&action_einstellungen,SIGNAL(triggered()),this,SLOT(funktion_einstellungen()));
    connect(&action_hilfe,SIGNAL(triggered()),this,SLOT(funktion_hilfe()));
    connect(&action_mauskoordinatenAnzeigen,SIGNAL(triggered()),this,SLOT(funktion_mauskoordinatenAnzeigen()));
    connect(&action_plot1Plot2Synchronisieren,SIGNAL(triggered()),this,SLOT(funktion_plot1Plot2Synchronisieren()));
    connect(&btn_okPloteigenschaften,SIGNAL(clicked()),this,SLOT(funktion_okPloteigenschaftenPlot1()));
    connect(&btn_okPloteigenschaften,SIGNAL(clicked()),this,SLOT(funktion_okPloteigenschaftenPlot2()));
    connect(&btn_abbrechenPloteigenschaften,SIGNAL(clicked()),this,SLOT(funktion_abbrechenPloteigenschaften()));
    connect(&listWidget_aktuelleMesswertePlot1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_ploteigenschaftenPlot1(QModelIndex)));
    connect(&listWidget_aktuelleMesswertePlot2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_ploteigenschaftenPlot2(QModelIndex)));
    connect(&lineEdit_aktuelleMessewertePlot1,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheAktuelleMessewertePlot1(QString)));
    connect(&lineEdit_aktuelleMessewertePlot2,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheAktuelleMessewertePlot2(QString)));
    connect(&lineEdit_messwerteEinzelnPlot1,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheMesswerteEinzelnPlot1(QString)));
    connect(&lineEdit_messwerteEinzelnPlot2,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheMesswerteEinzelnPlot2(QString)));
    connect(&lineEdit_messwertGruppiertPlot1,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheMesswertGruppiertPlot1(QString)));
    connect(&lineEdit_messwertGruppiertPlot2,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheMesswertGruppiertPlot2(QString)));
    connect(&lineEdit_offeneProjekte,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheoffeneProjekte(QString)));
    connect(&lineEdit_messwerteEinzelnMessdatengruppen,SIGNAL(textChanged(QString)),this,SLOT(funktion_sucheMesswerteMessdatengruppen(QString)));
    connect(&listWidget_aktuelleMesswertePlot1,SIGNAL(clicked(QModelIndex)),this,SLOT(funktion_aktuelleMesswertePlot1Angeklickt()));
    connect(&listWidget_aktuelleMesswertePlot2,SIGNAL(clicked(QModelIndex)),this,SLOT(funktion_aktuelleMesswertePlot2Angeklickt()));
    connect(&tabWidget_messdatenPlot1,SIGNAL(tabBarClicked(int)),this,SLOT(funktion_tabWidgetPlot1Angeklickt()));
    connect(&tabWidget_messdatenPlot2,SIGNAL(tabBarClicked(int)),this,SLOT(funktion_tabWidgetPlot2Angeklickt()));
    connect(&listWidget_messwerteEinzelnPlot1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_messwertePlot1Hinzufuegen(QModelIndex)));
    connect(&listWidget_messwerteEinzelnPlot2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_messwertePlot2Hinzufuegen(QModelIndex)));
    connect(&listWidget_messwertGruppiertPlot1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_messwertgruppePlot1Hinzufuegen(QModelIndex)));
    connect(&listWidget_messwertGruppiertPlot2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(funktion_messwertgruppePlot2Hinzufuegen(QModelIndex)));
    connect(&btn_messwertZuGruppeHinzufuegen,SIGNAL(clicked()),this,SLOT(funktion_messwertZuGruppeHinzufuegen()));
    connect(&listWidget_messwerteEinzelnMessdatengruppen,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(funktion_messwertZuGruppeHinzufuegen(QListWidgetItem*)));
    connect(&btn_messwertVonGruppeEntfernen,SIGNAL(clicked()),this,SLOT(funktion_messwertVonGruppeEntfernen()));
    connect(&btn_neueMesswertgruppeErstellen,SIGNAL(clicked()),this,SLOT(funktion_neueMesswertgruppeErstellen()));
    connect(&btn_messwertgruppeEntfernen,SIGNAL(clicked()),this,SLOT(funktion_messwertgruppeEntfernen()));
    connect(&lineEdit_nameMesswertgruppe,SIGNAL(textChanged(QString)),this,SLOT(funktion_messwertgruppeNameAendern(QString)));
    connect(&comboBox_messwertgruppen,SIGNAL(currentIndexChanged(int)),this,SLOT(funktion_comboBoxMesswertgruppen()));
    connect(&btn_okEinstellungen,SIGNAL(clicked()),this,SLOT(funktion_okEinstellungen()));
    connect(&btn_abbrechenEinstellungen,SIGNAL(clicked()),this,SLOT(funktion_abbrechenEinstellungen()));
    connect(&btn_okHintergrundfarbe,SIGNAL(clicked()),this,SLOT(funktion_okHintergrundfarbe()));
    connect(&btn_abbrechenHintergrundfarbe,SIGNAL(clicked()),this,SLOT(funktion_abbrechenHintergrundfarbe()));
}

/**
 * @brief MainWindow::messdatengruppenSpeichern
 * Es wird eine Textdatei Messdatengruppen.txt erzeugt, in der die Messdatengruppen abgespeichert werden.
 */
void MainWindow::messdatengruppenSpeichern()
{
    writefile.open("Messdatengruppen.txt");

    for(int i = 0; i < maxAnzahlMesswertgruppen; i++)
    {        
        for(int j = 0; j < maxAnzahlElementeMesswertgruppe; j++)
        {
            if(j == 0 && messdatengruppen[i][j].text() != "")
            {
                writefile << "Gruppe:";
            }

            if(messdatengruppen[i][j].text() != "")
            {
                writefile << messdatengruppen[i][j].text().toStdString();
                writefile << endl;
            }
        }
    }
    writefile.close();
}

/**
 * @brief MainWindow::messdatengruppenLaden
 * Bei jedem Aufruf der Einstellungen wird die Textdatei Messdatengruppen.txt ausgelesen. Die Messdatengruppen und die dazugehoerenden Messwerte
 * werden in dem QListWidgetItem-Array messdatengruppen gespeichert.
 */
void MainWindow::messdatengruppenLaden()
{
    readfile.open("Messdatengruppen.txt");
    zeile = -1;
    spalte = 0;

    if(readfile.is_open())
    {
        while(getline(readfile,text))
        {
            if(text.find("Gruppe:",0) != std::string::npos)
            {
                spalte = 0;
                zeile++;
                text = text.substr(7);
                messdatengruppen[zeile][spalte].setText(QString::fromStdString(text));
                spalte++;
            }
            else
            {
                messdatengruppen[zeile][spalte].setText(QString::fromStdString(text));
                spalte++;
            }
        }

        readfile.close();
    }
}

/**
 * @brief MainWindow::messwertgruppenListWidgetErzeugen
 * Hier werden in den ListWidgets Messdatengruppen von Plot1 und Plot2 die Messdatengruppen hinzugefuegt. Hierzu wird das QListWidgetItem-Array
 * messdatengruppen ausgelesen. Die Messdatengruppennamen werden direkt in das ListWidget geschrieben. Die dazugehoerenden Messwerte werden in
 * Form eines Tooltipps der Messwertgruppen angezeigt.
 */
void MainWindow::messwertgruppenListWidgetErzeugen()
{
    messdatengruppenLaden();

    listWidget_messwertGruppiertPlot1.clear();
    listWidget_messwertGruppiertPlot2.clear();

    for(int i = 0; i < maxAnzahlMesswertgruppen; i++)
    {
        text = "";
        if(messdatengruppen[i][0].text() != "")
        {
            listWidget_messwertGruppiertPlot1.addItem(messdatengruppen[i][0].text());
            listWidget_messwertGruppiertPlot2.addItem(messdatengruppen[i][0].text());

            for(int j = 1; j < maxAnzahlElementeMesswertgruppe; j++)
            {
                if(messdatengruppen[i][j].text() != "")
                {
                    text = text + namenMessdaten[messdatengruppen[i][j].text().toInt()].toStdString() + "\n";
                }
            }
            listWidget_messwertGruppiertPlot1.item(i)->setToolTip(QString::fromStdString(text));
            listWidget_messwertGruppiertPlot2.item(i)->setToolTip(QString::fromStdString(text));
        }
    }
}

/**
 * @brief MainWindow::funktion_laden
 * Hier koennen Projekte geladen werden. Die Messdaten koennen daraufhin in den Plots angezeigt werden.
 */
void MainWindow::funktion_laden()
{
    QFileDialog::getOpenFileName();
}

/**
 * @brief MainWindow::funktion_speichern
 */
void MainWindow::funktion_speichern()
{
    //QFileDialog::getSaveFileName();
    ////////////////////////////////////////////////////////////////////////////
    qDebug() << "SPEICHERN";
    //d_plot1->messdatenZeichnen(1);
    QTime start(0,0,0);
    Datalog->liveAnforderungDaten(10);
    Datalog->logfileLesen(10, start, QTime::currentTime());


    datenaufb->getAllData(10); //Test

            d_plot1->messdatenZeichnen(1);
            funktion_zoomZuruecksetzenPlot1();
    ////////////////////////////////////////////////////////////////////////////
}

/**
 * @brief MainWindow::funktion_neu
 */
void MainWindow::funktion_neu()
{
    ////////////////////////////////////////////////////////////////////////////
    qDebug() << "NEU";
    if(starttt == true){starttt = false;}
    else{starttt = true;}
    Datalog->liveAnforderungDaten(10);
    ////////////////////////////////////////////////////////////////////////////
}

/**
 * @brief MainWindow::funktion_einFenster
 * Hier wird Plot2 ausgeblendet.
 */
void MainWindow::funktion_einFenster()
{
    einFensterAusgewaehlt = true;
    splitter_plot2MesswertePlot2.setVisible(false);

}

/**
 * @brief MainWindow::funktion_zweiFenster
 * Hier wird Plot2 eingeblendet.
 */
void MainWindow::funktion_zweiFenster()
{
    einFensterAusgewaehlt = false;
    splitter_plot2MesswertePlot2.setVisible(true);

}

/**
 * @brief MainWindow::funktion_messwerttabelleEinblenden
 * Hier wird das ListWidget mit den Messwertnamen eingeblendet.
 */
void MainWindow::funktion_messwerttabelleEinblenden()
{
    messwerttabelleEingeblendet = true;

    tabWidget_messdatenPlot1.setVisible(true);
    tabWidget_messdatenPlot2.setVisible(true);

    action_messwerttabelleEinblenden.setEnabled(false);
    action_messwerttabelleAusblenden.setEnabled(true);
}

/**
 * @brief MainWindow::funktion_messwerttabelleAusblenden
 * Hier wird das ListWidget mit den Messwertnamen ausgeblendet.
 */
void MainWindow::funktion_messwerttabelleAusblenden()
{
    messwerttabelleEingeblendet = false;

    tabWidget_messdatenPlot1.setVisible(false);
    tabWidget_messdatenPlot2.setVisible(false);

    action_messwerttabelleEinblenden.setEnabled(true);
    action_messwerttabelleAusblenden.setEnabled(false);
}

/**
 * @brief MainWindow::funktion_projektordnerEinblenden
 * Hier wird das ListWidget mit den aktuell geoeffneten Projekten eingeblendet.
 */
void MainWindow::funktion_projektordnerEinblenden()
{
    projektordnerEingeblendet = true;

    widget_offeneProjekte.setVisible(true);

    action_projektordnerEinblenden.setEnabled(false);
    action_projektordnerAusblenden.setEnabled(true);
}

/**
 * @brief MainWindow::funktion_projektordnerAusblenden
 * Hier wird das ListWidget mit den aktuell geoeffneten Projekten ausgeblendet.
 */
void MainWindow::funktion_projektordnerAusblenden()
{
    projektordnerEingeblendet = false;

    widget_offeneProjekte.setVisible(false);

    action_projektordnerEinblenden.setEnabled(true);
    action_projektordnerAusblenden.setEnabled(false);
}

/**
 * @brief MainWindow::funktion_ansichtWiederherstellen
 * Diese Funktion stellt die Standardansicht wieder her. Es wird Plot1 angezeigt und die ListWidgets mit den Messwertnamen und den offenen Projekten
 * eingeblendet.
 */
void MainWindow::funktion_ansichtWiederherstellen()
{
    funktion_einFenster();
    funktion_projektordnerEinblenden();
    funktion_messwerttabelleEinblenden();
    d_plot1->setXAxisValue(0,10);
    d_plot1->setYAxisValue(0,200);
    d_plot2->setXAxisValue(0,10);
    d_plot2->setYAxisValue(0,200);
    d_plot1->setCanvasBackground(QBrush(QColor( 0, 87, 174 )));
    d_plot2->setCanvasBackground(QBrush(QColor( 0, 87, 174 )));
}

/**
 * @brief MainWindow::funktion_fahrerfunk
 * Hier wird der Aufbau einer Funkverbindung zum Fahrer mit einem Klick auf den Button Fahrerfunk (fahrerfunkStatus ist true) angefordert.
 * Mit einem erneuten Klick auf den Button Fahrerfunk (fahrerfunkstatus ist false) wird die Funkverbindung getrennt.
 *
 */
void MainWindow::funktion_fahrerfunk()
{
    if(fahrerfunkStatus)
    {
        btn_fahrerfunk.setStyleSheet("background-color: red; color: white; font-size: 10pt; font: bold");
        fahrerfunkStatus = false;
    }
    else
    {
        btn_fahrerfunk.setStyleSheet("background-color: green; color: white; font-size: 10pt; font: bold");
        fahrerfunkStatus = true;
    }
}

/**
 * @brief MainWindow::mousePressEvent
 * @param event
 * Es werden die Achsenwerte beider Plots abgefragt. Die Position, bei der die linke Maustatste gedrueckt wird, wird in positionMausAlt gespeichert.
 * Falls Plot verschieben aktiv ist, wird beim Druecken der Maus das Mauszeigersymbol geaendert.
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        xAxisMinPlot1 = d_plot1->getXAxisMin();
        xAxisMaxPlot1 = d_plot1->getXAxisMax();
        yAxisMinPlot1 = d_plot1->getYAxisMin();
        yAxisMaxPlot1 = d_plot1->getYAxisMax();
        xAxisMinPlot2 = d_plot2->getXAxisMin();
        xAxisMaxPlot2 = d_plot2->getXAxisMax();
        yAxisMinPlot2 = d_plot2->getYAxisMin();
        yAxisMaxPlot2 = d_plot2->getYAxisMax();

        positionMausAlt = event->globalPos();
        positionMausAltFuerY = positionMausAlt;
    }

    if(event->button() == Qt::LeftButton && action_plotVerschieben.isChecked())
    {
        d_plot1->canvas()->setCursor(Qt::ClosedHandCursor);
        d_plot2->canvas()->setCursor(Qt::ClosedHandCursor);
    }
}

/**
 * @brief MainWindow::mouseReleaseEvent
 * @param event
 * Die Position, bei der die linke Maustaste losgelassen wird, wird in positionMausNeu gespeichert.
 *
 * Anhand positionMausAlt und positionMausNeu wird festgestellt, ob sich der Mausklick innerhalb von Plot1 oder Plot2 befunden hat. Dazu
 * werden die beiden Mauspositionen mit den Positionen der beiden Plots verglichen.
 *
 * Wenn xZoom, yZoom oder RechteckZoom aktiviert ist, werden positionMausAlt und positionMausNeu dazu verwendet, die neuen x- und y-Achsengrenzen
 * zu berechnen.
 *
 * Wenn herauszoomen aktiviert ist, wird aus Plot1 oder Plot2 um 40 Prozent herausgezoomt.
 *
 * Wenn plotVerschieben aktiviert ist, erscheint bei gedrueckter Maus ein anderes Maussymbol.
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    positionMausNeu = event->globalPos();
    positionMausNeuFuerY = positionMausNeu;

    // Bestimmen, ob sich Maus innerhalb von Plot1 befindet
    if(positionMausAlt.x() > d_plot1->mapToGlobal(d_plot1->rect().topLeft()).x() \
            && positionMausAlt.x() < d_plot1->mapToGlobal(d_plot1->rect().topRight()).x() \
            && positionMausNeu.x() > d_plot1->mapToGlobal(d_plot1->rect().topLeft()).x() \
            && positionMausNeu.x() < d_plot1->mapToGlobal(d_plot1->rect().topRight()).x() \
            && positionMausAlt.y() > d_plot1->mapToGlobal(d_plot1->rect().topLeft()).y() \
            && positionMausAlt.y() < d_plot1->mapToGlobal(d_plot1->rect().bottomLeft()).y() \
            && positionMausNeu.y() > d_plot1->mapToGlobal(d_plot1->rect().topLeft()).y() \
            && positionMausNeu.y() < d_plot1->mapToGlobal(d_plot1->rect().bottomLeft()).y())
    {
        mausInnerhalbPlot1 = true;
    }

    // Bestimmen, ob sich Maus innerhalb von Plot2 befindet
    if(positionMausAlt.x() > d_plot2->mapToGlobal(d_plot2->rect().topLeft()).x() \
            && positionMausAlt.x() < d_plot2->mapToGlobal(d_plot2->rect().topRight()).x() \
            && positionMausNeu.x() > d_plot2->mapToGlobal(d_plot2->rect().topLeft()).x() \
            && positionMausNeu.x() < d_plot2->mapToGlobal(d_plot2->rect().topRight()).x() \
            && positionMausAlt.y() > d_plot2->mapToGlobal(d_plot2->rect().topLeft()).y() \
            && positionMausAlt.y() < d_plot2->mapToGlobal(d_plot2->rect().bottomLeft()).y() \
            && positionMausNeu.y() > d_plot2->mapToGlobal(d_plot2->rect().topLeft()).y() \
            && positionMausNeu.y() < d_plot2->mapToGlobal(d_plot2->rect().bottomLeft()).y()
            && d_plot2->isVisible())
    {
        mausInnerhalbPlot2 = true;
    }

    //x-Achse fuer Plot1 berechnen; bei xZoom und rechteckZoom
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot1 && (action_xAchseHineinZoomen.isChecked() || action_rechteckZoomen.isChecked()))
    {
        xBreitePlot = d_plot1->size().width()-52-8;
        xPosPlot = d_plot1->mapToGlobal(d_plot1->rect().topLeft()).x();

        if(positionMausAlt.x() > positionMausNeu.x())
        {
            point_zwischenspeicher = positionMausAlt;
            positionMausAlt = positionMausNeu;
            positionMausNeu = point_zwischenspeicher;
        }

        xPosMausInPlot = positionMausAlt.x()-xPosPlot-52;

        deltaXMaus = positionMausNeu.x()-positionMausAlt.x();

        xAxisMinNeuPlot1 = xAxisMinPlot1 + (xAxisMaxPlot1-xAxisMinPlot1)/xBreitePlot*xPosMausInPlot;
        xAxisMaxNeuPlot1 = xAxisMinNeuPlot1 + deltaXMaus/xBreitePlot*(xAxisMaxPlot1-xAxisMinPlot1);

        d_plot1->setXAxisValue(xAxisMinNeuPlot1,xAxisMaxNeuPlot1);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot2->setXAxisValue(xAxisMinNeuPlot1,xAxisMaxNeuPlot1);
        }
    }

    //x-Achse fuer Plot2 berechnen; bei xZoom und rechteckZoom
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot2 && (action_xAchseHineinZoomen.isChecked() || action_rechteckZoomen.isChecked()))
    {
        xBreitePlot = d_plot2->size().width()-52-8;
        xPosPlot = d_plot2->mapToGlobal(d_plot1->rect().topLeft()).x();

        if(positionMausAlt.x() > positionMausNeu.x())
        {
            point_zwischenspeicher = positionMausAlt;
            positionMausAlt = positionMausNeu;
            positionMausNeu = point_zwischenspeicher;
        }

        xPosMausInPlot = positionMausAlt.x()-xPosPlot-52;

        deltaXMaus = positionMausNeu.x()-positionMausAlt.x();

        xAxisMinNeuPlot2 = xAxisMinPlot2 + (xAxisMaxPlot2-xAxisMinPlot2)/xBreitePlot*xPosMausInPlot;
        xAxisMaxNeuPlot2 = xAxisMinNeuPlot2 + deltaXMaus/xBreitePlot*(xAxisMaxPlot2-xAxisMinPlot2);

        d_plot2->setXAxisValue(xAxisMinNeuPlot2,xAxisMaxNeuPlot2);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot1->setXAxisValue(xAxisMinNeuPlot2,xAxisMaxNeuPlot2);
        }
    }

    //y-Achse fuer Plot1 berechnen; bei yZoom und rechteckZoom
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot1 && (action_yAchseHineinZoomen.isChecked() || action_rechteckZoomen.isChecked()))
    {
        if(positionMausAlt.y() < positionMausNeu.y())
        {
            point_zwischenspeicher = positionMausAlt;
            positionMausAlt = positionMausNeu;
            positionMausNeu = point_zwischenspeicher;
        }

        deltaYMaus = abs(positionMausNeu.y()-positionMausAlt.y());
        yBreitePlot = d_plot1->size().height()-58-8;
        yPosPlot = d_plot1->mapToGlobal(d_plot1->rect().bottomLeft()).y();
        yPosMausInPlot = abs(positionMausAlt.y()-yPosPlot-8)-61;

        yAxisMinNeuPlot1 = yAxisMinPlot1 + (yAxisMaxPlot1-yAxisMinPlot1)/yBreitePlot*yPosMausInPlot;
        yAxisMaxNeuPlot1 = yAxisMinNeuPlot1 + deltaYMaus/yBreitePlot*(yAxisMaxPlot1-yAxisMinPlot1);

        d_plot1->setYAxisValue(yAxisMinNeuPlot1,yAxisMaxNeuPlot1);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot2->setYAxisValue(yAxisMinNeuPlot1,yAxisMaxNeuPlot1);
        }
    }

    //y-Achse fuer Plot2 berechnen; bei yZoom und rechteckZoom
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot2 && (action_yAchseHineinZoomen.isChecked() || action_rechteckZoomen.isChecked()))
    {
        if(positionMausAlt.y() < positionMausNeu.y())
        {
            point_zwischenspeicher = positionMausAlt;
            positionMausAlt = positionMausNeu;
            positionMausNeu = point_zwischenspeicher;
        }

        deltaYMaus = abs(positionMausNeu.y()-positionMausAlt.y());
        yBreitePlot = d_plot2->size().height()-58-8;
        yPosPlot = d_plot2->mapToGlobal(d_plot1->rect().bottomLeft()).y();
        yPosMausInPlot = abs(positionMausAlt.y()-yPosPlot-8)-61;

        yAxisMinNeuPlot2 = yAxisMinPlot2 + (yAxisMaxPlot2-yAxisMinPlot2)/yBreitePlot*yPosMausInPlot;
        yAxisMaxNeuPlot2 = yAxisMinNeuPlot2 + deltaYMaus/yBreitePlot*(yAxisMaxPlot2-yAxisMinPlot2);

        d_plot2->setYAxisValue(yAxisMinNeuPlot2,yAxisMaxNeuPlot2);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot1->setYAxisValue(yAxisMinNeuPlot2,yAxisMaxNeuPlot2);
        }
    }

    //aus Plot1 herauszoomen
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot1 && action_herausZoomen.isChecked())
    {
        xAxisValuePlot1 = xAxisMaxPlot1 - xAxisMinPlot1;
        yAxisValuePlot1 = yAxisMaxPlot1 - yAxisMinPlot1;
        xAxisMinNeuPlot1 = xAxisMinPlot1 - 0.2*xAxisValuePlot1;
        xAxisMaxNeuPlot1 = xAxisMaxPlot1 + 0.2*xAxisValuePlot1;
        yAxisMinNeuPlot1 = yAxisMinPlot1 - 0.2*yAxisValuePlot1;
        yAxisMaxNeuPlot1 = yAxisMaxPlot1 + 0.2*yAxisValuePlot1;

        d_plot1->setXAxisValue(xAxisMinNeuPlot1,xAxisMaxNeuPlot1);
        d_plot1->setYAxisValue(yAxisMinNeuPlot1,yAxisMaxNeuPlot1);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot2->setXAxisValue(xAxisMinNeuPlot1,xAxisMaxNeuPlot1);
            d_plot2->setYAxisValue(yAxisMinNeuPlot1,yAxisMaxNeuPlot1);
        }
    }

    //aus Plot2 herauszoomen
    if(event->button() == Qt::LeftButton && mausInnerhalbPlot2 && action_herausZoomen.isChecked())
    {
        xAxisValuePlot2 = xAxisMaxPlot2 - xAxisMinPlot2;
        yAxisValuePlot2 = yAxisMaxPlot2 - yAxisMinPlot2;
        xAxisMinNeuPlot2 = xAxisMinPlot2 - 0.2*xAxisValuePlot2;
        xAxisMaxNeuPlot2 = xAxisMaxPlot2 + 0.2*xAxisValuePlot2;
        yAxisMinNeuPlot2 = yAxisMinPlot2 - 0.2*yAxisValuePlot2;
        yAxisMaxNeuPlot2 = yAxisMaxPlot2 + 0.2*yAxisValuePlot2;

        d_plot2->setXAxisValue(xAxisMinNeuPlot2,xAxisMaxNeuPlot2);
        d_plot2->setYAxisValue(yAxisMinNeuPlot2,yAxisMaxNeuPlot2);

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot1->setXAxisValue(xAxisMinNeuPlot2,xAxisMaxNeuPlot2);
            d_plot1->setYAxisValue(yAxisMinNeuPlot2,yAxisMaxNeuPlot2);
        }
    }

    //Cursor aendern, wenn Aktion "Verschieben" aktiviert ist
    if(event->button() == Qt::LeftButton && action_plotVerschieben.isChecked())
    {
        d_plot1->canvas()->setCursor(Qt::OpenHandCursor);
        d_plot2->canvas()->setCursor(Qt::OpenHandCursor);
    }

    //Zoom von Plot1 zuruecksetzen
    if(action_zoomZuruecksetzen.isChecked() && mausInnerhalbPlot1)
    {
        funktion_zoomZuruecksetzenPlot1();

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot2->setXAxisValue(d_plot1->getXAxisMin(),d_plot1->getXAxisMax());
            d_plot2->setYAxisValue(d_plot1->getYAxisMin(),d_plot1->getYAxisMax());
        }
    }

    //Zoom von Plot2 zuruecksetzen
    if(action_zoomZuruecksetzen.isChecked() && mausInnerhalbPlot2)
    {
        funktion_zoomZuruecksetzenPlot2();

        if(action_plot1Plot2Synchronisieren.isChecked())
        {
            d_plot1->setXAxisValue(d_plot2->getXAxisMin(),d_plot2->getXAxisMax());
            d_plot1->setYAxisValue(d_plot2->getYAxisMin(),d_plot2->getYAxisMax());
        }
    }

    //x- und y-Achsenwerte von Plot1 und Plot2 synchronisieren
    if(action_plot1Plot2Synchronisieren.isChecked() && action_plotVerschieben.isChecked() && mausInnerhalbPlot1)
    {
        d_plot2->setXAxisValue(d_plot1->getXAxisMin(),d_plot1->getXAxisMax());
        d_plot2->setYAxisValue(d_plot1->getYAxisMin(),d_plot1->getYAxisMax());
    }

    //x- und y-Achsenwerte von Plot1 und Plot2 synchronisieren
    if(action_plot1Plot2Synchronisieren.isChecked() && action_plotVerschieben.isChecked() && mausInnerhalbPlot2)
    {
        d_plot1->setXAxisValue(d_plot2->getXAxisMin(),d_plot2->getXAxisMax());
        d_plot1->setYAxisValue(d_plot2->getYAxisMin(),d_plot2->getYAxisMax());
    }

    mausInnerhalbPlot1 = false;
    mausInnerhalbPlot2 = false;
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

/**
 * @brief MainWindow::keyReleaseEvent
 * @param event
 * Bei Druecken der Entf-Taste auf der Tastatur wird der aktuell ausgewaehlte Messwert aus dem Plot geloescht.
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        d_plot1->messdatenEntfernen(aktuellGeploteteMesswertePlot1[listWidget_aktuelleMesswertePlot1.currentRow()]);

        for(int i = listWidget_aktuelleMesswertePlot1.currentRow(); i < maxAnzahlMessdaten-1; i++)
        {
            aktuellGeploteteMesswertePlot1[i] = aktuellGeploteteMesswertePlot1[i+1];
        }

        qDeleteAll(listWidget_aktuelleMesswertePlot1.selectedItems());
        qDeleteAll(listWidget_aktuelleMesswertePlot2.selectedItems());
    }

    if(event->key() == Qt::Key_Escape)
    {
        funktion_maus();
    }
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

/**
 * @brief MainWindow::funktion_hintergrundfarbeAendern
 * Im Color-Dialog wird die Hintergrundfarbe der Plots angezeigt.
 */
void MainWindow::funktion_hintergrundfarbeAendern()
{
    colorDialogHintergrundfarbe->setCurrentColor(d_plot1->canvasBackground().color());
    widget_hintergrundfarbe.show();
}

/**
 * @brief MainWindow::funktion_okHintergrundfarbe
 * Die Hintergrundfarbe der Plots wird in die im Color-Dialog ausgewaehlte Farbe geaendert.
 */
void MainWindow::funktion_okHintergrundfarbe()
{
    d_plot1->setCanvasBackground(QBrush(colorDialogHintergrundfarbe->currentColor()));
    d_plot2->setCanvasBackground(QBrush(colorDialogHintergrundfarbe->currentColor()));
    widget_hintergrundfarbe.close();
}

/**
 * @brief MainWindow::funktion_abbrechenHintergrundfarbe
 * Beim Abbrechen des Color-Dialogs soll nichts weiteres passieren.
 */
void MainWindow::funktion_abbrechenHintergrundfarbe()
{
    widget_hintergrundfarbe.close();
}

/**
 * @brief MainWindow::funktion_plotVerschieben
 * Wenn plotVerschieben aktiviert ist, wird bei beiden Plots der plotPanner aktiviert. Dieser dient zum Verschieben der Plots.
 * Zusaetzlich wird der Mauszeiger geandert.
 */
void MainWindow::funktion_plotVerschieben()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_plotVerschieben.setChecked(true);

    plotPannerPlot1->setEnabled(true);
    plotPannerPlot2->setEnabled(true);

    d_plot1->canvas()->setCursor(Qt::OpenHandCursor);
    d_plot2->canvas()->setCursor(Qt::OpenHandCursor);
}

/**
 * @brief MainWindow::funktion_xAchseZoomen
 * Beim Aktivieren von xAchseZoomen wird der Mauszeiger abgeaendert.
 */
void MainWindow::funktion_xAchseZoomen()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_xAchseHineinZoomen.setChecked(true);
    d_plot1->canvas()->setCursor(Qt::SizeHorCursor);
    d_plot2->canvas()->setCursor(Qt::SizeHorCursor);
}

/**
 * @brief MainWindow::funktion_yAchseZoomen
 * Beim Aktivieren von yAchseZoomen wird der Mauszeiger abgeaendert.
 */
void MainWindow::funktion_yAchseZoomen()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_yAchseHineinZoomen.setChecked(true);
    d_plot1->canvas()->setCursor(Qt::SizeVerCursor);
    d_plot2->canvas()->setCursor(Qt::SizeVerCursor);
}

void MainWindow::funktion_rechteckZoomen()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_rechteckZoomen.setChecked(true);
}

/**
 * @brief MainWindow::funktion_herausZoomen
 * Beim Aktivieren von herausZoomen wird der Mauszeiger geaendert.
 */
void MainWindow::funktion_herausZoomen()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_herausZoomen.setChecked(true);
    d_plot1->canvas()->setCursor(QCursor(QPixmap(":bilder/Bilder/zoomMinus.png")));
    d_plot2->canvas()->setCursor(QCursor(QPixmap(":bilder/Bilder/zoomMinus.png")));
}

/**
 * @brief MainWindow::funktion_zoomZuruecksetzen
 *
 */
void MainWindow::funktion_zoomZuruecksetzen()
{
    funktion_maus();
    action_maus.setChecked(false);
    action_zoomZuruecksetzen.setChecked(true);
}

/**
 * @brief MainWindow::funktion_maus
 *
 */
void MainWindow::funktion_maus()
{
    action_maus.setChecked(true);
    action_xAchseHineinZoomen.setChecked(false);
    action_yAchseHineinZoomen.setChecked(false);
    action_rechteckZoomen.setChecked(false);
    action_plotVerschieben.setChecked(false);
    action_herausZoomen.setChecked(false);
    action_zoomZuruecksetzen.setChecked(false);
    d_plot1->canvas()->setCursor(Qt::ArrowCursor);
    d_plot2->canvas()->setCursor(Qt::ArrowCursor);
    plotPannerPlot1->setEnabled(false);
    plotPannerPlot2->setEnabled(false);
}

/**
 * @brief MainWindow::funktion_zoomZuruecksetzenPlot1
 * Die minimal und maximal auftretenden x- und y-Werte aller angezeigten Messwerte von Plot1 werden ermittelt. Mithilfe dieser Werte werden die neuen
 * x- und y-Achsen bemasst.
 */
void MainWindow::funktion_zoomZuruecksetzenPlot1()
{
    listWidget_offeneProjekte.clear();
    listWidget_offeneProjekte.addItem(QString::number(d_plot1->getMinimalerXWertMessdaten()));
    listWidget_offeneProjekte.addItem(QString::number(d_plot1->getMaximalerXWertMessdaten()));
    listWidget_offeneProjekte.addItem(QString::number(d_plot1->getMinimalerYWertMessdaten()));
    listWidget_offeneProjekte.addItem(QString::number(d_plot1->getMaximalerYWertMessdaten()));


    if(listWidget_aktuelleMesswertePlot1.count() != 0)
    {
        xAxisMinNeuPlot1 = d_plot1->getMinimalerXWertMessdaten() - 0.1*(d_plot1->getMaximalerXWertMessdaten() - d_plot1->getMinimalerXWertMessdaten());
        xAxisMaxNeuPlot1 = d_plot1->getMaximalerXWertMessdaten() + 0.1*(d_plot1->getMaximalerXWertMessdaten() - d_plot1->getMinimalerXWertMessdaten());
        yAxisMinNeuPlot1 = d_plot1->getMinimalerYWertMessdaten() - 0.1*(d_plot1->getMaximalerYWertMessdaten() - d_plot1->getMinimalerYWertMessdaten());
        yAxisMaxNeuPlot1 = d_plot1->getMaximalerYWertMessdaten() + 0.1*(d_plot1->getMaximalerYWertMessdaten() - d_plot1->getMinimalerYWertMessdaten());

        d_plot1->setXAxisValue(xAxisMinNeuPlot1,xAxisMaxNeuPlot1);
        d_plot1->setYAxisValue(yAxisMinNeuPlot1,yAxisMaxNeuPlot1);
    }
}

/**
 * @brief MainWindow::funktion_zoomZuruecksetzenPlot2
 * Die minimal und maximal auftretenden x- und y-Werte aller angezeigten Messwerte von Plot2 werden ermittelt. Mithilfe dieser Werte werden die neuen
 * x- und y-Achsen bemasst.
 */
void MainWindow::funktion_zoomZuruecksetzenPlot2()
{
    if(listWidget_aktuelleMesswertePlot2.count() != 0)
    {
        xAxisMinNeuPlot2 = d_plot2->getMinimalerXWertMessdaten() - 0.1*(d_plot2->getMaximalerXWertMessdaten() - d_plot2->getMinimalerXWertMessdaten());
        xAxisMaxNeuPlot2 = d_plot2->getMaximalerXWertMessdaten() + 0.1*(d_plot2->getMaximalerXWertMessdaten() - d_plot2->getMinimalerXWertMessdaten());
        yAxisMinNeuPlot2 = d_plot2->getMinimalerYWertMessdaten() - 0.1*(d_plot2->getMaximalerYWertMessdaten() - d_plot2->getMinimalerYWertMessdaten());
        yAxisMaxNeuPlot2 = d_plot2->getMaximalerYWertMessdaten() + 0.1*(d_plot2->getMaximalerYWertMessdaten() - d_plot2->getMinimalerYWertMessdaten());

        d_plot2->setXAxisValue(xAxisMinNeuPlot2,xAxisMaxNeuPlot2);
        d_plot2->setYAxisValue(yAxisMinNeuPlot2,yAxisMaxNeuPlot2);
    }
}

/**
 * @brief MainWindow::funktion_okPloteigenschaftenPlot1
 * Die im Color-Dialog ausgewaehlte Farbe wird dem pen zugewiesen.
 * Die Breite des Stifts wird dem slider abgefragt und dem pen zugewiesen.
 * Die radioButtons der Linienarten werden abgefragt und dem pen zugewiesen.
 * Der pen wird der aktuell ausgewaehlten Messkurve von Plot1 zugewiesen und erhaelt damit diese Stifteigenschaften.
 */
void MainWindow::funktion_okPloteigenschaftenPlot1()
{
    listWidgetItem->setBackgroundColor(colorDialogPlot->currentColor());

    pen.setColor(colorDialogPlot->currentColor());
    pen.setWidth(slider_dickePlot.value());

    if(radioBtn_durchgezogeneLinie.isChecked())
    {
        pen.setStyle(Qt::SolidLine);
    }
    else if(radioBtn_gestrichelteLinie.isChecked())
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(radioBtn_gepunkteteLinie.isChecked())
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(radioBtn_punktStrichLinie.isChecked())
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(radioBtn_punktPunktStrichLinie.isChecked())
    {
        pen.setStyle(Qt::DashDotDotLine);
    }

    //*******************************hier fehlt noch was*****************
    //Ploteigenschaften der aktuellen Kurve muessen noch gesetzt werden
    //*******************************************************************

    //
    listWidget_offeneProjekte.addItem(QString::number(positionItemPlot1Ploteigenschaften));
    if(listWidget_aktuelleMesswertePlot1.count() != 0)
    {
        d_plot1->setPenStyle(pen,aktuellGeploteteMesswertePlot1[positionItemPlot1Ploteigenschaften]);
    }

    widget_ploteigenschaften.close();
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

/**
 * @brief MainWindow::funktion_okPloteigenschaftenPlot2
 * Die im Color-Dialog ausgewaehlte Farbe wird dem pen zugewiesen.
 * Die Breite des Stifts wird dem slider abgefragt und dem pen zugewiesen.
 * Die radioButtons der Linienarten werden abgefragt und dem pen zugewiesen.
 * Der pen wird der aktuell ausgewaehlten Messkurve von Plot1 zugewiesen und erhaelt damit diese Stifteigenschaften.
 */
void MainWindow::funktion_okPloteigenschaftenPlot2()
{
    listWidgetItem->setBackgroundColor(colorDialogPlot->currentColor());

    pen.setColor(colorDialogPlot->currentColor());
    pen.setWidth(slider_dickePlot.value());

    if(radioBtn_durchgezogeneLinie.isChecked())
    {
        pen.setStyle(Qt::SolidLine);
    }
    else if(radioBtn_gestrichelteLinie.isChecked())
    {
        pen.setStyle(Qt::DashLine);
    }
    else if(radioBtn_gepunkteteLinie.isChecked())
    {
        pen.setStyle(Qt::DotLine);
    }
    else if(radioBtn_punktStrichLinie.isChecked())
    {
        pen.setStyle(Qt::DashDotLine);
    }
    else if(radioBtn_punktPunktStrichLinie.isChecked())
    {
        pen.setStyle(Qt::DashDotDotLine);
    }

    //*******************************hier fehlt noch was*****************
    //Ploteigenschaften der aktuellen Kurve muessen noch gesetzt werden
    //*******************************************************************

    if(listWidget_aktuelleMesswertePlot2.count() != 0)
    {
    d_plot2->setPenStyle(pen,positionItemPlot2Ploteigenschaften);
    }

    widget_ploteigenschaften.close();
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

void MainWindow::funktion_abbrechenPloteigenschaften()
{
    widget_ploteigenschaften.close();
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

/**
 * @brief MainWindow::funktion_ploteigenschaftenPlot1
 * @param index:
 */
void MainWindow::funktion_ploteigenschaftenPlot1(QModelIndex index)
{
    //positionItemPlot1Ploteigenschaften = index.row();
    funktion_ploteigenschaftenPlot1(index.row());
}

void MainWindow::funktion_ploteigenschaftenPlot1(int index)
{
    text = listWidget_aktuelleMesswertePlot1.item(index)->text().toStdString();
    positionItemPlot1Ploteigenschaften = index;

    if(text.find("Gruppe",0) == std::string::npos)
    {
        listWidgetItem = listWidget_aktuelleMesswertePlot1.item(index);

        pen = d_plot1->getPenStyle(aktuellGeploteteMesswertePlot1[positionItemPlot1Ploteigenschaften]);

        colorDialogPlot->setCurrentColor(pen.color());
        slider_dickePlot.setValue(pen.width());

        if(pen.style() == Qt::SolidLine)
        {
            radioBtn_durchgezogeneLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashLine)
        {
            radioBtn_gestrichelteLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DotLine)
        {
            radioBtn_gepunkteteLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashDotLine)
        {
            radioBtn_punktStrichLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashDotDotLine)
        {
            radioBtn_punktPunktStrichLinie.setChecked(true);
        }

        widget_ploteigenschaften.setWindowTitle("Ploteigenschaften: " + listWidgetItem->text());
        widget_ploteigenschaften.show();
    }
}

void MainWindow::funktion_ploteigenschaftenPlot2(QModelIndex index)
{
    positionItemPlot2Ploteigenschaften = index.row();
    funktion_ploteigenschaftenPlot2(positionItemPlot2Ploteigenschaften);
}

void MainWindow::funktion_ploteigenschaftenPlot2(int index)
{
    text = listWidget_aktuelleMesswertePlot2.item(index)->text().toStdString();

    if(text.find("Gruppe",0) == std::string::npos)
    {
        listWidgetItem = listWidget_aktuelleMesswertePlot2.item(index);

        pen = d_plot2->getPenStyle(index);

        colorDialogPlot->setCurrentColor(pen.color());
        slider_dickePlot.setValue(pen.width());

        if(pen.style() == Qt::SolidLine)
        {
            radioBtn_durchgezogeneLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashLine)
        {
            radioBtn_gestrichelteLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DotLine)
        {
            radioBtn_gepunkteteLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashDotLine)
        {
            radioBtn_punktStrichLinie.setChecked(true);
        }
        else if(pen.style() == Qt::DashDotDotLine)
        {
            radioBtn_punktPunktStrichLinie.setChecked(true);
        }

        widget_ploteigenschaften.setWindowTitle("Ploteigenschaften: " + listWidgetItem->text());
        widget_ploteigenschaften.show();
    }
}

/**
 * @brief MainWindow::funktion_sucheMesswerteEinzelnPlot1
 * @param arg1 enthaelt den im Label geschriebenen string
 *
 */
void MainWindow::funktion_sucheMesswerteEinzelnPlot1(const QString &arg1)
{
    for(int i = 0; i < listWidget_messwerteEinzelnPlot1.count(); i++)
    {
        listWidget_messwerteEinzelnPlot1.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_messwerteEinzelnPlot1.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_messwerteEinzelnPlot1.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheMesswertGruppiertPlot1(const QString &arg1)
{
    for(int i = 0; i < listWidget_messwertGruppiertPlot1.count(); i++)
    {
        listWidget_messwertGruppiertPlot1.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_messwertGruppiertPlot1.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_messwertGruppiertPlot1.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheMesswerteEinzelnPlot2(const QString &arg1)
{
    for(int i = 0; i < listWidget_messwerteEinzelnPlot2.count(); i++)
    {
        listWidget_messwerteEinzelnPlot2.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_messwerteEinzelnPlot2.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_messwerteEinzelnPlot2.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheMesswertGruppiertPlot2(const QString &arg1)
{
    for(int i = 0; i < listWidget_messwertGruppiertPlot2.count(); i++)
    {
        listWidget_messwertGruppiertPlot2.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_messwertGruppiertPlot2.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_messwertGruppiertPlot2.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheAktuelleMessewertePlot1(const QString &arg1)
{
    for(int i = 0; i < listWidget_aktuelleMesswertePlot1.count(); i++)
    {
        listWidget_aktuelleMesswertePlot1.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_aktuelleMesswertePlot1.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_aktuelleMesswertePlot1.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheAktuelleMessewertePlot2(const QString &arg1)
{
    for(int i = 0; i < listWidget_aktuelleMesswertePlot2.count(); i++)
    {
        listWidget_aktuelleMesswertePlot2.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_aktuelleMesswertePlot2.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_aktuelleMesswertePlot2.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheoffeneProjekte(const QString &arg1)
{
    for(int i = 0; i < listWidget_offeneProjekte.count(); i++)
    {
        listWidget_offeneProjekte.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_offeneProjekte.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_offeneProjekte.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_sucheMesswerteMessdatengruppen(const QString &arg1)
{
    for(int i = 0; i < listWidget_messwerteEinzelnMessdatengruppen.count(); i++)
    {
        listWidget_messwerteEinzelnMessdatengruppen.item(i)->setHidden(false);
        qstring_suchtext = arg1.toLower();
        qstring_text = listWidget_messwerteEinzelnMessdatengruppen.item(i)->text().toLower();
        if(!qstring_text.contains(qstring_suchtext))
        {
            listWidget_messwerteEinzelnMessdatengruppen.item(i)->setHidden(true);
        }
    }
}

void MainWindow::funktion_aktuelleMesswertePlot1Angeklickt()
{
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

void MainWindow::funktion_aktuelleMesswertePlot2Angeklickt()
{
    listWidget_aktuelleMesswertePlot1.clearSelection();
}

void MainWindow::funktion_tabWidgetPlot1Angeklickt()
{
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

void MainWindow::funktion_tabWidgetPlot2Angeklickt()
{
    listWidget_aktuelleMesswertePlot1.clearSelection();
    listWidget_aktuelleMesswertePlot2.clearSelection();
}

void MainWindow::funktion_messwertePlot1Hinzufuegen(QModelIndex index)
{
    aktuellGeploteteMesswertePlot1[listWidget_aktuelleMesswertePlot1.count()] = index.row();
    //vektorAktuellGeploteteMesswertePlot1.append(index.row());
    listWidget_aktuelleMesswertePlot1.addItem(listWidget_messwerteEinzelnPlot1.item(index.row())->text());
    d_plot1->messdatenZeichnen(index.row());

    funktion_ploteigenschaftenPlot1(listWidget_aktuelleMesswertePlot1.count()-1);
}

void MainWindow::funktion_messwertePlot2Hinzufuegen(QModelIndex index)
{
    aktuellGeploteteMesswertePlot2[listWidget_aktuelleMesswertePlot2.count()] = index.row();
    //vektorAktuellGeploteteMesswertePlot2.append(index.row());
    listWidget_aktuelleMesswertePlot2.addItem(listWidget_messwerteEinzelnPlot2.item(index.row())->text());
    d_plot2->messdatenZeichnen(index.row());

    funktion_ploteigenschaftenPlot2(listWidget_aktuelleMesswertePlot2.count()-1);
}

void MainWindow::funktion_messwertgruppePlot1Hinzufuegen(QModelIndex index)
{
    for(int i = 1; i < maxAnzahlElementeMesswertgruppe; i++)
    {
        if(messdatengruppen[index.row()][i].text() != "")
        {
            aktuellGeploteteMesswertePlot1[listWidget_aktuelleMesswertePlot1.count()] = messdatengruppen[index.row()][i].text().toInt();
            listWidget_aktuelleMesswertePlot1.addItem(namenMessdaten[messdatengruppen[index.row()][i].text().toInt()]);
            d_plot1->messdatenZeichnen(messdatengruppen[index.row()][i].text().toInt());
        }
    }
}

void MainWindow::funktion_messwertgruppePlot2Hinzufuegen(QModelIndex index)
{
    for(int i = 1; i < maxAnzahlElementeMesswertgruppe; i++)
    {
        if(messdatengruppen[index.row()][i].text() != "")
        {
            aktuellGeploteteMesswertePlot2[listWidget_aktuelleMesswertePlot2.count()] = messdatengruppen[index.row()][i].text().toInt();
            listWidget_aktuelleMesswertePlot2.addItem(namenMessdaten[messdatengruppen[index.row()][i].text().toInt()]);
            d_plot2->messdatenZeichnen(messdatengruppen[index.row()][i].text().toInt());
        }
    }
}

void MainWindow::funktion_einstellungen()
{
    messdatengruppenLaden();


    comboBox_messwertgruppen.clear();
    lineEdit_nameMesswertgruppe.clear();
    listWidget_messwertgruppen.clear();
    lineEdit_messwerteEinzelnMessdatengruppen.clear();

    for(int i = 0; i < maxAnzahlMesswertgruppen; i++)
    {
        if(messdatengruppen[i][0].text() != "")
        {
            comboBox_messwertgruppen.addItem(messdatengruppen[i][0].text());
        }
    }

    lineEdit_nameMesswertgruppe.setText(comboBox_messwertgruppen.currentText());

    widget_einstellungen.show();

}

void MainWindow::funktion_messwertZuGruppeHinzufuegen()
{
    if(comboBox_messwertgruppen.currentIndex() != -1)
    {
        listWidget_messwertgruppen.addItem(listWidget_messwerteEinzelnMessdatengruppen.currentItem()->text());
        messdatengruppen[comboBox_messwertgruppen.currentIndex()][listWidget_messwertgruppen.count()].setText(QString::number(listWidget_messwerteEinzelnMessdatengruppen.currentRow()));
    }
    funktion_neu();
}

void MainWindow::funktion_messwertZuGruppeHinzufuegen(QListWidgetItem *item)
{
    if(comboBox_messwertgruppen.currentIndex() != -1)
    {
        listWidget_messwertgruppen.addItem(item->text());
        messdatengruppen[comboBox_messwertgruppen.currentIndex()][listWidget_messwertgruppen.count()].setText(QString::number(listWidget_messwerteEinzelnMessdatengruppen.currentRow()));
    }
}

void MainWindow::funktion_messwertVonGruppeEntfernen()
{
    messdatengruppen[comboBox_messwertgruppen.currentIndex()][listWidget_messwertgruppen.currentRow()+1].setText("");
    qDeleteAll(listWidget_messwertgruppen.selectedItems());

    for(int i = listWidget_messwertgruppen.currentRow()+1; i < listWidget_messwertgruppen.count()+1; i++)
    {
        if(messdatengruppen[comboBox_messwertgruppen.currentIndex()][i+1].text() != "")
        {
            messdatengruppen[comboBox_messwertgruppen.currentIndex()][i].setText(messdatengruppen[comboBox_messwertgruppen.currentIndex()][i+1].text());
        }
    }
    messdatengruppen[comboBox_messwertgruppen.currentIndex()][listWidget_messwertgruppen.count()+1].setText("");
}

void MainWindow::funktion_neueMesswertgruppeErstellen()
{
    if(comboBox_messwertgruppen.count() == -1)
    {
        messdatengruppen[0][0].setText("Neue Messwertgruppe");
    }
    else
    {
        messdatengruppen[comboBox_messwertgruppen.count()][0].setText("Neue Messwertgruppe");
    }

    comboBox_messwertgruppen.addItem("Neue Messwertgruppe");

    comboBox_messwertgruppen.setCurrentIndex(comboBox_messwertgruppen.count()-1);
    lineEdit_nameMesswertgruppe.setFocus();
    lineEdit_nameMesswertgruppe.setSelection(0,lineEdit_nameMesswertgruppe.text().count());

}

void MainWindow::funktion_messwertgruppeEntfernen()
{
    if(comboBox_messwertgruppen.count() != 0)
    {
        for(int i = comboBox_messwertgruppen.currentIndex(); i < maxAnzahlMesswertgruppen-1; i++)
        {
            for(int j = 0; j < maxAnzahlElementeMesswertgruppe; j++)
            {
                messdatengruppen[i][j].setText(messdatengruppen[i+1][j].text());
            }
        }

        comboBox_messwertgruppen.removeItem(comboBox_messwertgruppen.count()-1);
        for(int i = 0; i < comboBox_messwertgruppen.count(); i++)
        {
            comboBox_messwertgruppen.setItemText(i,messdatengruppen[i][0].text());
        }

        if(comboBox_messwertgruppen.count() == 0)
        {
            lineEdit_nameMesswertgruppe.clear();
            listWidget_messwertgruppen.clear();
        }
        else
        {
            comboBox_messwertgruppen.setCurrentIndex(0);
        }
    }

}

void MainWindow::funktion_messwertgruppeNameAendern(const QString &arg1)
{
    if(comboBox_messwertgruppen.count() != 0)
    {
        comboBox_messwertgruppen.setItemText(comboBox_messwertgruppen.currentIndex(),arg1);
        messdatengruppen[comboBox_messwertgruppen.currentIndex()][0].setText(arg1);
    }
}

void MainWindow::funktion_comboBoxMesswertgruppen()
{
    if(comboBox_messwertgruppen.count() != 0)
    {
        lineEdit_nameMesswertgruppe.setText(messdatengruppen[comboBox_messwertgruppen.currentIndex()][0].text());

        listWidget_messwertgruppen.clear();
        for(int i = 1; i < maxAnzahlElementeMesswertgruppe; i++)
        {
            if(messdatengruppen[comboBox_messwertgruppen.currentIndex()][i].text() != "")
            {
                listWidget_messwertgruppen.addItem(namenMessdaten[messdatengruppen[comboBox_messwertgruppen.currentIndex()][i].text().toInt()]);
            }
        }
    }
}

void MainWindow::funktion_okEinstellungen()
{
    messdatengruppenSpeichern();
    messwertgruppenListWidgetErzeugen();

    widget_einstellungen.close();
}

void MainWindow::funktion_abbrechenEinstellungen()
{
    widget_einstellungen.close();
}

void MainWindow::funktion_hilfe()
{
    QDesktopServices::openUrl(QUrl("hilfe.html"));
}

void MainWindow::funktion_mauskoordinatenAnzeigen()
{
    if(mauskoordinatenAnzeigen)
    {
        d_plot1->mauskoordinatenDeaktivieren();
        d_plot2->mauskoordinatenDeaktivieren();

        mauskoordinatenAnzeigen = false;
    }
    else
    {
        d_plot1->mauskoordinatenAktivieren();
        d_plot2->mauskoordinatenAktivieren();
        mauskoordinatenAnzeigen = true;
    }

    action_mauskoordinatenAnzeigen.setChecked(mauskoordinatenAnzeigen);
}

void MainWindow::funktion_plot1Plot2Synchronisieren()
{
    if(action_plot1Plot2Synchronisieren.isChecked())
    {
        d_plot2->setXAxisValue(d_plot1->getXAxisMin(),d_plot1->getXAxisMax());
        d_plot2->setYAxisValue(d_plot1->getYAxisMin(),d_plot1->getYAxisMax());
    }
}
