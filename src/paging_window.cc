#include "paging_window.h"

#include <QicsDataModelDefault.h>
#include <QicsTable.h>

#include <QLabel>

PagingWindow::PagingWindow() {
    // dimensions of the data model
    const int numRows = 10;
    const int numCols = 5;

    // create the data model
    QicsDataModel *dm = new QicsDataModelDefault(numRows, numCols);

    // populate the data model with some data
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j) dm->setItem(i, j, QicsDataInt(i * j));

    // create the table, using the data model we created above
    QicsTable *table = new QicsTable(dm, 0);
    table->setWindowTitle(QObject::tr("你好 👋"));

    // make sure the table is only as large as necessary
    table->setVisibleRows(numRows);
    table->setVisibleColumns(numCols);

    // Add a title widget to the top of the table
    QLabel *label = new QLabel(QObject::tr("Hello World, Table"), table);
    label->setAlignment(Qt::AlignCenter);
    table->setTopTitleWidget(label);

    table->activateWindow();
    table->show();
}
PagingWindow::~PagingWindow() {}