#include "plot.h"


class Canvas: public QwtPlotCanvas
{
public:
    Canvas( QwtPlot *plot = NULL ):
        QwtPlotCanvas( plot )
    {
        // The backing store is important, when working with widget
        // overlays ( f.e rubberbands for zooming ).
        // Here we don't have them and the internal
        // backing store of QWidget is good enough.

        setPaintAttribute( QwtPlotCanvas::BackingStore, false );
        setBorderRadius( 10 );

        if ( QwtPainter::isX11GraphicsSystem() )
        {
#if QT_VERSION < 0x050000
            // Even if not liked by the Qt development, Qt::WA_PaintOutsidePaintEvent
            // works on X11. This has a nice effect on the performance.

            setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
#endif

            // Disabling the backing store of Qt improves the performance
            // for the direct painter even more, but the canvas becomes
            // a native window of the window system, receiving paint events
            // for resize and expose operations. Those might be expensive
            // when there are many points and the backing store of
            // the canvas is disabled. So in this application
            // we better don't disable both backing stores.

            if ( testPaintAttribute( QwtPlotCanvas::BackingStore ) )
            {
                setAttribute( Qt::WA_PaintOnScreen, true );
                setAttribute( Qt::WA_NoSystemBackground, true );
            }
        }

        setupPalette();
    }


private:
    void setupPalette()
    {
        QPalette pal = palette();

#if QT_VERSION >= 0x040400
        QLinearGradient gradient;
        gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
        gradient.setColorAt( 0.0, QColor( 0, 87, 174 ) );

        pal.setBrush( QPalette::Window, QBrush( gradient ) );
#else
        pal.setBrush( QPalette::Window, QBrush( color ) );
#endif

        // QPalette::WindowText is used for the curve color
        pal.setColor( QPalette::WindowText, Qt::green );

        setPalette( pal );
    }
};

void Plot::setup(Datenaufbereitung *datenauf)
{
    Datenaufbe = datenauf;
}

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_paintedPoints( 0 ),
    d_interval( 0.0 , 10.0 ),
    d_timerId( -1 )
{
    d_directPainter = new QwtPlotDirectPainter();

    setAutoReplot( false );
    setCanvas( new Canvas() );

    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle( QwtPlot::xBottom, "Time [s]" );
    //setAxisScale( QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue() );
    setAxisScale(QwtPlot::xBottom,1,10);
    setAxisScale( QwtPlot::yLeft, -200.0, 200.0 );

    magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setMouseButton( Qt::NoButton );
    magnifier->setWheelFactor(1.2);

    picker = new QwtPlotPicker( canvas() );
    picker->setTrackerMode( QwtPlotPicker::AlwaysOn );
    picker->setTrackerFont(QFont("Times",10));

    grid = new QwtPlotGrid();
    grid->setPen( Qt::gray, 0.0, Qt::DotLine );
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( true );
    grid->enableYMin( false );
    grid->attach( this );

    d_origin = new QwtPlotMarker();
    d_origin->setLineStyle( QwtPlotMarker::Cross );
    d_origin->setValue(0,0);
    d_origin->setLinePen( Qt::gray, 0.0, Qt::DashLine );
    d_origin->attach( this );

    d_curve = new QwtPlotCurve();
    d_curve->setStyle( QwtPlotCurve::Lines );
    d_curve->setPen( canvas()->palette().color( QPalette::WindowText ) );
    d_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    d_curve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );
    d_curve->attach( this );

    for(int i = 0; i < anzahlD_curves; i++)
    {
        d_curve = new QwtPlotCurve();
        d_curve->setStyle( QwtPlotCurve::Lines );
        d_curve->setPen( canvas()->palette().color( QPalette::WindowText ) );
        d_curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        d_curve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );
        d_curve->attach( this );
        d_kurve.append(d_curve);
    }

    namenMessdaten[0] = "a";
    namenMessdaten[1] = "b";
    namenMessdaten[2] = "c";
    namenMessdaten[3] = "d";
    namenMessdaten[4] = "e";
    namenMessdaten[5] = "f";
    namenMessdaten[6] = "g";
    namenMessdaten[7] = "h";
    namenMessdaten[8] = "i";
    namenMessdaten[9] = "j";


}

Plot::~Plot()
{
//    delete d_directPainter;
//    delete magnifier;
//    delete grid;
//    delete picker;
//    delete d_origin;
//    delete d_curve;
//    d_kurve.~QVector();
}

void Plot::start()
{
    d_clock.start();
    d_timerId = startTimer( 10 );
}

void Plot::replot()
{
    CurveData *data = static_cast<CurveData *>( d_curve->data() );
    data->values().lock();

    QwtPlot::replot();
    d_paintedPoints = data->size();

    data->values().unlock();
}

void Plot::setIntervalLength( double interval )
{
    if ( interval > 0.0 && interval != d_interval.width() )
    {
        d_interval.setMaxValue( d_interval.minValue() + interval );
        setAxisScale( QwtPlot::xBottom,
                      d_interval.minValue(), d_interval.maxValue() );

        replot();
    }
}

void Plot::setXAxisValue(double minimalerWert, double maximalerWert)
{
    setAxisScale(QwtPlot::xBottom,minimalerWert,maximalerWert);
    d_interval.setMinValue(minimalerWert);
    d_interval.setMaxValue(maximalerWert);

    replot();
}

void Plot::setYAxisValue(double minimalerWert, double maximalerWert)
{
    setAxisScale(QwtPlot::yLeft,minimalerWert,maximalerWert);
    d_interval.setMinValue(minimalerWert);
    d_interval.setMaxValue(maximalerWert);

    replot();
}

double Plot::getXAxisMin()
{
    replot();
    return axisScaleDiv(QwtPlot::xBottom).lowerBound();
}

double Plot::getXAxisMax()
{
    replot();
    return axisScaleDiv(QwtPlot::xBottom).upperBound();
}

double Plot::getYAxisMin()
{
    replot();
    return axisScaleDiv(QwtPlot::yLeft).lowerBound();
}

double Plot::getYAxisMax()
{
    replot();
    return axisScaleDiv(QwtPlot::yLeft).upperBound();
}

/**
 * @brief Plot::getMinimalerXWertMessdaten
 * sucht im Plot nach dem kleinsten x-Wert
 * @return gibt kleinsten x-Wert als double zurueck
 */
double Plot::getMinimalerXWertMessdaten()
{
    minimalerXWert = 10000;

    for(int i = 0; i < anzahlD_curves; i++)
    {
        if(d_kurve[i]->dataSize() > 0 && d_kurve[i]->minXValue() < minimalerXWert)
        {
            minimalerXWert = d_kurve[i]->minXValue();
        }
    }
    return minimalerXWert;
}

/**
 * @brief Plot::getMaximalerXWertMessdaten
 * sucht im Plot nach dem groessten x-Wert
 * @return gibt groessten x-Wert als double zurueck
 */
double Plot::getMaximalerXWertMessdaten()
{
    maximalerXWert = -10000;

    for(int i = 0; i < anzahlD_curves; i++)
    {
        if(d_kurve[i]->dataSize() > 0 && d_kurve[i]->maxXValue() > maximalerXWert)
        {
            maximalerXWert = d_kurve[i]->maxXValue();
        }
    }
    return maximalerXWert;
}

/**
 * @brief Plot::getMinimalerYWertMessdaten
 * sucht im Plot nach dem kleinsten y-Wert
 * @return gibt kleinsten y-Wert als double zurueck
 */
double Plot::getMinimalerYWertMessdaten()
{
    minimalerYWert = 10000;

    for(int i = 0; i < anzahlD_curves; i++)
    {
        if(d_kurve[i]->dataSize() > 0 && d_kurve[i]->minYValue() < minimalerYWert)
        {
            minimalerYWert = d_kurve[i]->minYValue();
        }
    }
    return minimalerYWert;
}

/**
 * @brief Plot::getMaximalerYWertMessdaten
 * sucht im Plot nach dem groessten y-Wert
 * @return gibt groessten y-Wert als double zurueck
 */
double Plot::getMaximalerYWertMessdaten()
{
    maximalerYWert = -10000;

    for(int i = 0; i < anzahlD_curves; i++)
    {
        if(d_kurve[i]->dataSize() > 0 && d_kurve[i]->maxYValue() > maximalerYWert)
        {
            maximalerYWert = d_kurve[i]->maxYValue();
        }
    }
    return maximalerYWert;
}

/**
 * @brief Plot::messdatenZeichnen
 * @param indexMessdaten: ID der Messdaten, die gezeichnet werden sollen; wird in der GUI ausgewaehlt
 * zeichnet die Messdaten der zugehoerigen ID
 */
void Plot::messdatenZeichnen(int indexMessdaten)
{
    ///////////////////////////////////////////////////

    QVector<double> x, y;
    for(int i = 0; i<Datenaufbe->bufferVector[10].size(); i++)
    {
        y.append(Datenaufbe->bufferVector[10].at(i).getWert());
        QTime temptime = Datenaufbe->bufferVector[10].at(i).getZeit();
        double temptimemsec = temptime.msec();
        double temptime2 = temptime.hour()*3600 + temptime.minute()*60 + temptime.second() + temptimemsec/1000;
        x.append(temptime2);
    }

    d_kurve[indexMessdaten]->setSamples(x,y);
    replot();

    ///////////////////////////////////////////////////
}

void Plot::messdatenEntfernen(int indexMessdaten)
{
    x.clear();
    y.clear();

    d_kurve[indexMessdaten]->setSamples(x,y);

    replot();
}


//leitet die Messdaten zur Klasse Datenaufbereitung weiter
//artDerAuswertung gibt an, um welche Auswertungsart es sich handelt: 0 fuer FFT, ...
//void Plot::messdatenZumAufbereitenWeiterleiten(int indexMessdaten, int artDerAuswertung)
//{
//    y.clear();

//    for(int i = 0; i < d_curve->dataSize(); i++)
//    {
//        y.append(d_curve->data()->sample(i).y());
//    }

//    if(artDerAuswertung == 0)
//    {
//        komplexeDaten = datenAufbereiten.fft(&y);
//    }

//    anzahlDaten = ceil(pow(2,log2(y.size())));

//    //x.clear();
//    //y.clear();
//    xwert = 0;

//    for(int i = 0; i < anzahlDaten; i++)
//    {
//        x.append(xwert);
//        y.append(abs(komplexeDaten[i]));
//        xwert++;
//    }

//    d_curve->setSamples(x,y);
//    d_curve->setStyle(QwtPlotCurve::Dots);
//    d_curve->setPen(QPen(Qt::green,5));

//    replot();
//}

/**
 * @brief Plot::getPenStyle
 * @param indexMessdaten: ID der Kurve, von dem PenStyle zurueckgegeben wird
 * @return gibt Linienart, Linienfarbe und Liniendicke zurueck
 */
QPen Plot::getPenStyle(int indexMessdaten)
{
    return d_kurve[indexMessdaten]->pen();
}

/**
 * @brief Plot::setPenStyle
 * @param pen: enthaelt Linienart, Linienfarbe und Liniendicke, die in der GUI ausgewaehlt wurden
 * @param indexMessdaten: ID der Kurve, von der PenStyle geandert werden soll
 */
void Plot::setPenStyle(QPen pen, int indexMessdaten)
{   
    d_kurve[indexMessdaten]->setPen(pen);
}

/**
 * @brief Plot::mauskoordinatenAktivieren
 * aktiviert im Plot die Koordinaten, die neben dem Mauspfeil angezeigt werden
 */
void Plot::mauskoordinatenAktivieren()
{
    picker->setEnabled(true);
}

/**
 * @brief Plot::mauskoordinatenDeaktivieren
 * deaktiviert im Plot die Koordinaten, die neben dem Mauspfeil angezeigt werden
 */
void Plot::mauskoordinatenDeaktivieren()
{
    picker->setEnabled(false);
}

void Plot::updateCurve()
{
    for(int i = 0; i < anzahlD_curves; i++)
    {
        CurveData *data = static_cast<CurveData *>( d_kurve[i]->data() );
        data->values().lock();

        const int numPoints = data->size();
        if ( numPoints > d_paintedPoints )
        {
            const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
            if ( doClip )
            {
                /*
                        Depending on the platform setting a clip might be an important
                        performance issue. F.e. for Qt Embedded this reduces the
                        part of the backing store that has to be copied out - maybe
                        to an unaccelerated frame buffer device.
                    */

                const QwtScaleMap xMap = canvasMap( d_curve->xAxis() );
                const QwtScaleMap yMap = canvasMap( d_curve->yAxis() );

                QRectF br = qwtBoundingRect( *data,
                                             d_paintedPoints - 1, numPoints - 1 );

                const QRect clipRect = QwtScaleMap::transform( xMap, yMap, br ).toRect();
                d_directPainter->setClipRegion( clipRect );
            }

            d_directPainter->drawSeries( d_kurve[i],
                                         d_paintedPoints - 1, numPoints - 1 );
            d_paintedPoints = numPoints;
        }

        data->values().unlock();
    }

//    CurveData *data = static_cast<CurveData *>( d_curve->data() );
//    data->values().lock();

//    const int numPoints = data->size();
//    if ( numPoints > d_paintedPoints )
//    {
//        const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
//        if ( doClip )
//        {
//            /*
//                    Depending on the platform setting a clip might be an important
//                    performance issue. F.e. for Qt Embedded this reduces the
//                    part of the backing store that has to be copied out - maybe
//                    to an unaccelerated frame buffer device.
//                */

//            const QwtScaleMap xMap = canvasMap( d_curve->xAxis() );
//            const QwtScaleMap yMap = canvasMap( d_curve->yAxis() );

//            QRectF br = qwtBoundingRect( *data,
//                                         d_paintedPoints - 1, numPoints - 1 );

//            const QRect clipRect = QwtScaleMap::transform( xMap, yMap, br ).toRect();
//            d_directPainter->setClipRegion( clipRect );
//        }

//        d_directPainter->drawSeries( d_curve,
//                                     d_paintedPoints - 1, numPoints - 1 );
//        d_paintedPoints = numPoints;
//    }

//    data->values().unlock();


}

void Plot::incrementInterval()
{    
    d_interval = QwtInterval( d_interval.maxValue(),
                              d_interval.maxValue() + d_interval.width() );

    CurveData *data = static_cast<CurveData *>( d_curve->data() );
    data->values().clearStaleValues( d_interval.minValue() );

    // To avoid, that the grid is jumping, we disable
    // the autocalculation of the ticks and shift them
    // manually instead.

    QwtScaleDiv scaleDiv = axisScaleDiv( QwtPlot::xBottom );
    scaleDiv.setInterval( d_interval );

    for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
    {
        QList<double> ticks = scaleDiv.ticks( i );
        for ( int j = 0; j < ticks.size(); j++ )
            ticks[j] += d_interval.width();
        scaleDiv.setTicks( i, ticks );
    }
    setAxisScaleDiv( QwtPlot::xBottom, scaleDiv );

    d_origin->setValue( d_interval.minValue() + d_interval.width() / 2.0, 0.0 );

    d_paintedPoints = 0;
    replot();
}

void Plot::timerEvent( QTimerEvent *event )
{
    if ( event->timerId() == d_timerId )
    {
        updateCurve();

        const double elapsed = d_clock.elapsed() / 1000.0;
        if ( elapsed > d_interval.maxValue() )
            incrementInterval();

        return;
    }

    QwtPlot::timerEvent( event );
}

void Plot::resizeEvent( QResizeEvent *event )
{
    d_directPainter->reset();
    QwtPlot::resizeEvent( event );
}

void Plot::showEvent( QShowEvent * )
{
    replot();
}

bool Plot::eventFilter( QObject *object, QEvent *event )
{
    if ( object == canvas() &&
         event->type() == QEvent::PaletteChange )
    {
        d_curve->setPen( canvas()->palette().color( QPalette::WindowText ) );
    }

    return QwtPlot::eventFilter( object, event );
}
