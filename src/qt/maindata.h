#ifndef MAINDATA_H
#define MAINDATA_H

#include <QObject>
#include <QString>
#include <QFile>
#include <memory>
#include "..\diff\diffLibrary.h"


class MainData : public QObject
{
    Q_OBJECT
public:
    typedef DiffLibrary::Diff<std::string> Diff;

    explicit MainData(QObject *parent = 0);

signals:
    void leftFileTextChanged(const QString &text);
    void rightFileTextChanged(const QString &text);
    void diffTextChanged(const QString &text);

public slots:
    void changeLeftFile(const QString &file_name);
    void changeRightFile(const QString &file_name);


private:
    bool openFiles();
    void closeFiles();


    QFile *leftFile;
    QFile *rightFile;

    std::tr1::shared_ptr<Diff> diffLib;
};

#endif // MAINDATA_H
