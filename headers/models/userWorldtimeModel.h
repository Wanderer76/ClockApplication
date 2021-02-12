#pragma once
#include<QAbstractListModel>
#include"headers/main.h"
#include"headers/helpers/savingSystemHelper.h"

class QTimer;

class UserWorldtimeModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<timeElement*>_elements;
    SavingSystemHelper*_savingSystemHelper;
    QTimer *_timer;
public:
    explicit UserWorldtimeModel();
    ~UserWorldtimeModel();
    Q_INVOKABLE void append(const QString&region,const QString&city);
    Q_INVOKABLE void remove(const int index);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
private slots:
    void updateUserTime();
    void writeData();
    void readData();
};
