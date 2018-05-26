#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_system_clock.h>
#include <QColorDialog>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <fstream>
#include <complex>
//#include <seriesdata.h>
#include "curvedata.h"
#include "signaldata.h"
#include <qwt_plot_grid.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>
#include <qwt_curve_fitter.h>
#include <qwt_painter.h>
#include <qevent.h>

#include <Datenaufbereitung.h>

using namespace std;

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotDirectPainter;


/**
 * In der Klasse Plot werden die Plots formatiert und die Daten gezeichnet.
 */
class Plot: public QwtPlot
{
    Q_OBJECT

public:
    void setup(Datenaufbereitung *datenauf);
    Plot( QWidget * = NULL );
    virtual ~Plot();

    void start();
    virtual void replot();

    virtual bool eventFilter( QObject *, QEvent * );

    double getXAxisMin();
    double getXAxisMax();
    double getYAxisMin();
    double getYAxisMax();
    double getMinimalerXWertMessdaten();
    double getMaximalerXWertMessdaten();
    double getMinimalerYWertMessdaten();
    double getMaximalerYWertMessdaten();
    void messdatenZeichnen(int indexMessdaten);
    void messdatenEntfernen(int indexMessdaten);
    void messdatenZumAufbereitenWeiterleiten(int indexMessdaten, int artDerAuswertung);
    QPen getPenStyle(int indexMessdaten);



public Q_SLOTS:
    void setIntervalLength( double );
    void setXAxisValue(double minimalerWert, double maximalerWert);
    void setYAxisValue(double minimalerWert, double maximalerWert);
    void setPenStyle(QPen pen, int indexMessdaten);
    void mauskoordinatenAktivieren();
    void mauskoordinatenDeaktivieren();


protected:
    virtual void showEvent( QShowEvent * );
    virtual void resizeEvent( QResizeEvent * );
    virtual void timerEvent( QTimerEvent * );

private:
    void updateCurve();
    void incrementInterval();

    /////////////////////////////////////////
    Datenaufbereitung *Datenaufbe;
    /////////////////////////////////////////

    QwtPlotMarker *d_origin;
    int d_paintedPoints;

    QwtPlotDirectPainter *d_directPainter;

    QwtPlotMagnifier *magnifier;

    QwtPlotGrid *grid;

    QwtInterval d_interval;
    int d_timerId;

    QwtSystemClock d_clock;

    QwtPlotPicker *picker;

    QwtPlotCurve *d_curve;

    QVector<double> x;
    QVector<double> y;

    QVector<QwtPlotCurve*> d_kurve;



    ifstream leseDaten;
    double xwert;
    string wert;
    string dateipfad;

    QString namenMessdaten[10];

    complex<double> *komplexeDaten;

    int anzahlDaten;
    int anzahlD_curves = 10;    //hier Anzahl von Kurven eintragen

    double minimalerXWert;
    double maximalerXWert;
    double minimalerYWert;
    double maximalerYWert;

};
