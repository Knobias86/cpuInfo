#include <QFile>
#include <QTimer>
#include <QDebug>

#include "filereader.h"

//static QString const FILE_URI = ":///simulationData.txt";
static QString const FILE_URI = "/proc/cpuinfo";
static quint16 const FILEREAD_INTERVAL = 1000;

FileReader::FileReader(QObject *parent) : QObject(parent)
{
    mReadFileTimer.reset(new QTimer(),
                  &QObject::deleteLater);

    connect(mReadFileTimer.data(),
            SIGNAL(timeout()),
            this,
            SLOT(readData()));

    mReadFileTimer.data()->start(FILEREAD_INTERVAL);
}

FileReader::~FileReader()
{
    emit finished();
}

bool FileReader::readFile(QByteArray &fileDatastream)
{
    QFile fileCpuInfo(FILE_URI);
    if(fileCpuInfo.exists())
    {
        if (fileCpuInfo.open(QFile::ReadOnly))
        {
            fileDatastream = fileCpuInfo.readAll();
            fileCpuInfo.close();
            if(fileDatastream.size() > 0)
            {
                return true;
            }
            else
            {
                qWarning() << __FUNCTION__
                           << "Problem: Empty file: "
                           << FILE_URI;
                return false;
            }
        }
        else
        {
            qWarning() << __FUNCTION__
                       << "Problem: Can't open file: "
                       << FILE_URI;
            return false;
        }
    }
    else
    {
        qWarning() << __FUNCTION__
                   << "Problem: Can't find File: "
                   << FILE_URI;
    }
    return false;
}

void FileReader::readData()
{
    QByteArray fileDatastream;
    if (readFile(fileDatastream))
    {
        emit updateDataStream(fileDatastream);
    }
}
