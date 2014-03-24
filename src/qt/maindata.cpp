#include "maindata.h"
#include <sstream>
using namespace std;


namespace
{
    void GetFileLines(QFile &file,
                      QString &strData,
                      MainData::Diff::ContainerType &container)
    {
        strData.resize(0);
        container.resize(0);
        if (file.isOpen())
        {
            while (!file.atEnd())
            {
                QByteArray buffer(file.readLine());
                strData.append(buffer);
                container.push_back(buffer.data());
            }
        }
    }
}



MainData::MainData(QObject *parent) :
    QObject(parent),
    leftFile(new QFile(this)),
    rightFile(new QFile(this))
{
}


void MainData::changeLeftFile(const QString &file_name)
{
    closeFiles();
    leftFile->setFileName(file_name);
    openFiles();
}

void MainData::changeRightFile(const QString &file_name)
{
    closeFiles();
    rightFile->setFileName(file_name);
    openFiles();
}

bool MainData::openFiles()
{
    if (leftFile->isOpen() ||
            rightFile->isOpen())
    {
        return false;
    }

    if (!leftFile->open(QFile::ReadOnly | QFile::Text) ||
            !rightFile->open(QFile::ReadOnly | QFile::Text))
    {
        closeFiles();
        return false;
    }

    QString buffer;
    Diff::ContainerType leftContainer,rightContainer;
    GetFileLines(*leftFile, buffer, leftContainer);
    emit leftFileTextChanged(buffer);

    GetFileLines(*rightFile, buffer, rightContainer);
    emit rightFileTextChanged(buffer);

    diffLib.reset(new Diff(leftContainer, rightContainer));
    diffLib->Compose();
    stringstream ssTemp;
    diffLib->GetSes().Serialize(ssTemp);
    emit diffTextChanged(QString(ssTemp.str().c_str()));
    return true;
}

void MainData::closeFiles()
{
    leftFile->close();
    rightFile->close();
}
