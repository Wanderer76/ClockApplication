#pragma once
#include <QObject>
#include<QAbstractListModel>
#include"headers/main.h"

#include"headers/helpers/timeloaderHelper.h"


class GlobalWorldtimeModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QVector<timeElement*> _elements;
    void createListOfElements();
    void parseJson(const QByteArray&);
public:
    explicit GlobalWorldtimeModel();
    ~GlobalWorldtimeModel();
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};
