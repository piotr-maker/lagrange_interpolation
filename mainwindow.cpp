#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *table_lt = new QHBoxLayout();
    table = new QTableView();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnWidth(0,100);
    table->setColumnWidth(1, 100);
    table->setMaximumWidth(216);
    table->setMinimumWidth(216);

    model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, "x");
    model->setHeaderData(1, Qt::Horizontal, "y");

    table->setModel(model);

    QVBoxLayout *table_menu_lt = new QVBoxLayout();
    table_menu_lt->addWidget(add_btn);
    table_menu_lt->addWidget(edit_btn);
    table_menu_lt->addWidget(remove_btn);
    table_menu_lt->addSpacerItem(new QSpacerItem(10,10,QSizePolicy::Minimum, QSizePolicy::Expanding));

    table_lt->addWidget(table);
    table_lt->addSpacing(20);
    table_lt->addLayout(table_menu_lt);
    table_lt->addSpacerItem(new QSpacerItem(10,10,QSizePolicy::Expanding));

    QHBoxLayout *main_menu_lt = new QHBoxLayout();
    main_menu_lt->addSpacerItem(new QSpacerItem(10,10, QSizePolicy::Expanding));
    main_menu_lt->addWidget(reset_btn);
    main_menu_lt->addWidget(calc_btn);
    main_menu_lt->addWidget(quit_btn);

    arg_in = new QDoubleSpinBox();
    QHBoxLayout *arg_lt = new QHBoxLayout();
    arg_lt->addWidget(new QLabel("Argument: "));
    arg_lt->addWidget(arg_in);

    QWidget *widget = new QWidget();
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QVBoxLayout *main = new QVBoxLayout();
    widget->setLayout(main);

    result = new QLabel("W = ");
    value = new QLabel("Value = ");

    main->addWidget(new QLabel("Points:"));
    main->addLayout(table_lt);
    main->addSpacing(20);
    main->addLayout(arg_lt);
    main->addSpacing(20);
    main->addWidget(result);
    main->addWidget(value);
    main->addSpacing(40);
    main->addLayout(main_menu_lt);

    emit disableCalc(true);
    this->setCentralWidget(widget);

    connect(this, SIGNAL(modelDataChanged()), this, SLOT(onModelDataChanged()));

    connect(this->add_btn, SIGNAL(clicked(bool)), this, SLOT(createForm()));
    connect(this->edit_btn, SIGNAL(clicked(bool)), this, SLOT(createForm()));
    connect(this->remove_btn, SIGNAL(clicked(bool)), this, SLOT(removePoint()));

    connect(this->reset_btn, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(this->quit_btn, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this->calc_btn, SIGNAL(clicked(bool)), this, SLOT(calculate()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::editPoint(double x, double y)
{
    int row = table->currentIndex().row();
    model->item(row, 0)->setText(QString::number(x));
    model->item(row, 1)->setText(QString::number(y));
    this->setDisabled(false);
    emit modelDataChanged();
}


void MainWindow::addPoint(double x, double y)
{
    this->setDisabled(false);
    QList<QStandardItem*> newRow;
    newRow.append(new QStandardItem(QString::number(x)));
    newRow.append(new QStandardItem(QString::number(y)));
    model->appendRow(newRow);
    if(model->rowCount() >= 2)
        emit disableCalc(false);
    emit modelDataChanged();
}

void MainWindow::removePoint()
{
    int row = table->currentIndex().row();
    model->removeRow(row);
    if(model->rowCount() < 2) emit disableCalc(true);
    emit modelDataChanged();
}

void MainWindow::onModelDataChanged()
{
    double x;
    double max_x = NAN;
    double min_x = NAN;

    for(int i = 0; i < model->rowCount(); i++) {
        x = model->item(i)->text().toDouble();
        if(x > max_x || isnan(max_x)) max_x = x;
        if(x < min_x || isnan(min_x)) min_x = x;
    }

    arg_in->setRange(min_x, max_x);
    result->setText("W = ");
    value->setText("Value = ");
}

void MainWindow::reset()
{
    lagrange.reset();
    model->clear();
    arg_in->setValue(0);
    result->setText("W = ");
    value->setText("Value = ");
    emit disableCalc(true);
}

void MainWindow::calculate()
{
    float x, y;
    lagrange.reset();

    for(int i = 0; i < model->rowCount(); i++) {
        x = model->item(i)->text().toDouble();
        y = model->item(i, 1)->text().toDouble();
        lagrange.addNode(x, y);
    }

    lagrange.setArgument(arg_in->value());
    lagrange.calculate();
    result->setText("W = " + QString(lagrange.getPolymonial().data()));
    value->setText("Value = " + QString::number(lagrange.getValue()));
}

void MainWindow::createForm()
{
    PointForm *form = new PointForm();
    bool addClicked = false;

    this->setDisabled(true);

    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if(button->text() == "Add")
        addClicked = true;

    if(!addClicked && model->rowCount() > 0) {
        int row = table->currentIndex().row();
        double x = model->item(row)->text().toDouble();
        double y = model->item(row, 1)->text().toDouble();
        form->set(x, y);
        connect(form, SIGNAL(save(double,double)), this, SLOT(editPoint(double, double)));
    } else
        connect(form, SIGNAL(save(double,double)), this, SLOT(addPoint(double, double)));
    connect(form, SIGNAL(finished(int)), this, SLOT(activate()));
}

void MainWindow::activate()
{
    this->setDisabled(false);
}

void MainWindow::disableCalc(bool disable)
{
    calc_btn->setDisabled(disable);
    arg_in->setDisabled(disable);
}

