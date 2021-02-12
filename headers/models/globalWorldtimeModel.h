#pragma once
#include <QObject>
#include<QAbstractListModel>
#include"headers/main.h"

class GlobalWorldtimeModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QVector<timeElement*> _elements;
    void createListOfElements();
public:
    explicit GlobalWorldtimeModel();
    ~GlobalWorldtimeModel();
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};

