#include "pointform.h"

PointForm::PointForm(QWidget *parent) : QDialog(parent)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *main_lt = new QVBoxLayout();

    QHBoxLayout *arg_lt = new QHBoxLayout();
    arg_lt->addWidget(new QLabel("x: "));
    arg_in = new QDoubleSpinBox();
    arg_in->setRange(-5000, 5000);
    arg_lt->addWidget(arg_in);

    QHBoxLayout *val_lt = new QHBoxLayout();
    val_lt->addWidget(new QLabel("y: "));
    val_in = new QDoubleSpinBox();
    val_in->setRange(-5000, 5000);
    val_lt->addWidget(val_in);

    QHBoxLayout *menu_lt = new QHBoxLayout();
    add_btn = new QPushButton("Add");
    cancel_btn = new QPushButton("Cancel");
    menu_lt->addSpacerItem(new QSpacerItem(10,10, QSizePolicy::Expanding));
    menu_lt->addWidget(add_btn);
    menu_lt->addWidget(cancel_btn);

    main_lt->addLayout(arg_lt);
    main_lt->addLayout(val_lt);
    main_lt->addSpacing(40);
    main_lt->addLayout(menu_lt);
    this->setLayout(main_lt);

    connect(this->add_btn, SIGNAL(clicked(bool)), this, SLOT(onAdd()));
    connect(this->cancel_btn, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->show();
}

void PointForm::onAdd()
{
    emit save(arg_in->value(), val_in->value());
    this->accept();
}

void PointForm::set(double x, double y)
{
    arg_in->setValue(x);
    val_in->setValue(y);
}
