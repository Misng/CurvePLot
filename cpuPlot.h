#ifndef CPUCURVE_H
#define CPUCURVE_H

#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_plot_canvas.h>
#include <Qwt/qwt_plot_layout.h>
#include <Qwt/qwt_legend.h>
#include <Qwt/qwt_scale_draw.h>

#include "cpustart.h"

#define HISTORY 60

class CputPlot : public QwtPlot
{
public:
    enum CpuData
    {
        User,
        System,
        Total,
        Idle,

        NCputData
    };

    CputPlot(QWidget * = 0);
    virtual ~CputPlot();

    const QwtPlotCurve * cpuCurve ( int id ) const
    {
        return data[id].curve;
    }
protected:
    void timerEvent(QTimerEvent *);
private:
    void showCurve( QwtPlotItem * ,bool );

    struct
    {
        QwtPlotCurve * curve;
        double data[HISTORY];
    }data[NCputData];

    double timeData[HISTORY];

    int dataCount;
    CpuStart cpuStart;
};

#endif // CPUCURVE_H
