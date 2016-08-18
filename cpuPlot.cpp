#include <QApplication>
#include <QtGui>
#include "cpuPlot.h"


class TimeScaleDraw : public QwtScaleDraw
{
public:
    TimeScaleDraw(const QTime &base) :
        baseTime(base)
    {
    }

    virtual QwtText label(double v) const//plot类会一次次的调用这个函数为坐标轴上的刻度标签赋值
    {
        QTime upTime = baseTime.addSecs(static_cast<int> (v));
        return upTime.toString("hh:mm:ss");
    }
private:
    QTime baseTime;
};

CputPlot::CputPlot(QWidget *parent) :
    QwtPlot(parent),
    dataCount(0)
{
    setAutoReplot(false);

    QwtPlotCanvas * canvas = new QwtPlotCanvas();
    canvas->setBorderRadius(10);//画布的周边角

    setCanvas(canvas);

    plotLayout()->setAlignCanvasToScales(true);//画布与轴水平对齐

    QwtLegend * legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);//设置图例的样式
    insertLegend(legend,QwtPlot::RightLegend);//设置图例和图例的位置

    setAxisTitle(QwtPlot::xBottom," SYstem Uptime [h:m:s]");
    setAxisScaleDraw(QwtPlot::xBottom,new TimeScaleDraw(QDateTime::currentDateTime().time()));


}

CputPlot::~CputPlot(){}

void CputPlot::timerEvent(QTimerEvent *)
{

}











int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

//    QWidget w;
//    w.setWindowTitle("ni hao CPU Time");

//    CputPlot* plot = new CputPlot(&w);
//    plot->setTitle("History");

//    w.show();

    QWidget vBox;
    vBox.setWindowTitle( "Cpu Plot" );

    CputPlot *plot = new CputPlot( &vBox );
//    plot->setTitle( "History" );

//    const int margin = 5;
//    plot->setContentsMargins( margin, margin, margin, margin );

//    QString info( "Press the legend to en/disable a curve" );

//    QLabel *label = new QLabel( info, &vBox );

//    QVBoxLayout *layout = new QVBoxLayout( &vBox );
//    layout->addWidget( plot );
//    layout->addWidget( label );

    vBox.resize( 600, 400 );
    vBox.show();


    return app.exec();
}
