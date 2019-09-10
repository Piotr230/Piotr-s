#include "mainwindow.h"
#include "ui_mainwindow.h"
/*#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets>
*/
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>

#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
  m_series(0),
  m_series_funkcja(0),
  m_axisX(new QValueAxis()),
  m_axisY(new QValueAxis()),
  m_step(0),
  m_x(0),
  m_y(0)
{
    ui->setupUi(this);
    QChartView *chartView;
    chartView = new QChartView(createSplineChart());
    //ui->
            //addWidget(chartView, 2, 1);
    QChart *chart = new QChart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QObject::connect(&m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);

    m_timer.setInterval(czas);

    m_series = new QSplineSeries(this);
    m_series_funkcja = new QSplineSeries(this);
    QPen green(Qt::red);
    QPen black(Qt::black);
    green.setWidth(3);
    black.setWidth(2);
    m_series->setPen(black);
    m_series_funkcja->setPen(green);
    m_series->append(m_x, m_y);
    m_series_funkcja->append(m_x,m_y);

    chart->addSeries(m_series);
    chart->addSeries(m_series_funkcja);

    pototWidth=chart->plotArea().width();

    chart->addAxis(m_axisX,Qt::AlignBottom);
    chart->addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series_funkcja->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_series_funkcja->attachAxis(m_axisY);
    m_axisX->setTickCount(5);
    m_axisX->setRange(0, 10);
    m_axisY->setRange(0, 5);
}
/*QChart *MainWindow::createSplineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;

            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);


    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}*/
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleTimeout()
{
    qreal x = pototWidth / m_axisX->tickCount();
    if(typ_wykresu == 1)
    {
        int uwzglednienieWyp = (wypelnienie)/100;
        m_series->append(m_x,skladowa_st);
        m_series_funkcja->append(0+okres*licznik,0);
        m_series_funkcja->append(okres*uwzglednienieWyp+okres*licznik,amplituda);
        m_series_funkcja->append(okres*uwzglednienieWyp+okres*licznik,0);

        licznik++;
    }else {

       m_series->append(m_x,skladowa_st);
       m_series_funkcja->append(0+okres*licznik,0);
       m_series_funkcja->append(0+okres*licznik,amplituda);
       m_series_funkcja->append(okres+okres*licznik,amplituda);
       m_series_funkcja->append(okres+okres*licznik,0);

       licznik++;
    }

    qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    m_x += y;
    //m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    //m_series->append(m_x, m_y);
    scroll(x, 0);
    if (m_x <= 100 || start_czy_stop==false)
        m_timer.stop();
}
void MainWindow::on_SPStartNaStop_valueChanged(int arg1)
{
    start_czy_stop=arg1;
}

void MainWindow::on_SPOkres_valueChanged(int arg1)
{
    okres=arg1;
}

void MainWindow::on_SPAmplituda_valueChanged(int arg1)
{
    amplituda=arg1;
}

void MainWindow::on_SPWypelnienie_valueChanged(int arg1)
{
    wypelnienie=arg1;
}

void MainWindow::on_SPCzas_valueChanged(int arg1)
{
    czas=arg1;
}

void MainWindow::on_CBTypWykresu_highlighted(int index)
{
    typ_wykresu = index;
}

void MainWindow::comboBox()
{
    ui->CBTypWykresu->addItem("Piloksztaltny",1);
    ui->CBTypWykresu->addItem("Prostokatny",2);
}
