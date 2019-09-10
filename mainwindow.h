#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}
//Wykres_Flaki(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleTimeout();

    void Start();
    void comboBox();
    void on_SPStartNaStop_valueChanged(int arg1);

    void on_SPOkres_valueChanged(int arg1);

    void on_SPAmplituda_valueChanged(int arg1);

    void on_SPWypelnienie_valueChanged(int arg1);

    void on_SPCzas_valueChanged(int arg1);
    void on_CBTypWykresu_highlighted(int index);

private:
    // QChart *createSplineChart() const;
private:
    Ui::MainWindow *ui;

    QChartView * m_charts;
    QTimer m_timer;
    QSplineSeries *m_series;
    QSplineSeries *m_series_funkcja;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;
    qreal czas;
    qreal skladowa_st;
    qreal okres;
    qreal typ_wykresu;
    qreal amplituda;
    qreal wypelnienie;
    bool start_czy_stop;
    int licznik =0;
    qreal pototWidth;
};

#endif // MAINWINDOW_H
