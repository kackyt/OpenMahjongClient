#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QVector>
#include "ClientQObject.h"

namespace Ui {
    class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
    OM_CONNECTION_TYPE getConnectionType() const;
    void getPlayerName(OMArray<OMString> &playernames) const;
    void getCompName(OMArray<OMString> &compnames) const;
    int getSessionNum() const;
    void getUrl(QUrl& url) const;
    void setClientQObject(OMClientQObject &obj);
private slots:
    void on_rdConnect_clicked();

    void on_rdCreate_clicked();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
