#ifndef POINTFORM_H
#define POINTFORM_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QBoxLayout>


class PointForm : public QDialog
{
    Q_OBJECT
public:
    explicit PointForm(QWidget *parent=nullptr);
    explicit PointForm(double x, double y, QWidget *parent=nullptr);
    void set(double x, double y);

signals:
    void save(double x, double y);

private slots:
    void onAdd();

private:
    QPushButton *add_btn;
    QPushButton *cancel_btn;

    QDoubleSpinBox *arg_in;
    QDoubleSpinBox *val_in;


};

#endif // POINTFORM_H
