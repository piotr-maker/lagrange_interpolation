#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QBoxLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>

#include "lagrange.h"
#include "pointform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void modelDataChanged();

private:
    QTableView *table;
    QStandardItemModel *model;

    Lagrange lagrange;

    QPushButton *add_btn = new QPushButton("Add");
    QPushButton *edit_btn = new QPushButton("Edit");
    QPushButton *remove_btn = new QPushButton("Remove");

    QPushButton *reset_btn = new QPushButton("Reset");
    QPushButton *calc_btn = new QPushButton("Calculate");
    QPushButton *quit_btn = new QPushButton("Quit");

    QDoubleSpinBox *arg_in = nullptr;

    QLabel *result = nullptr;
    QLabel *value = nullptr;

private slots:
    void addPoint(double x, double y);
    void editPoint(double x, double y);
    void removePoint();
    void onModelDataChanged();
    void reset();
    void calculate();
    void createForm();
    void activate();
    void disableCalc(bool disable);
};

#endif // MAINWINDOW_H
