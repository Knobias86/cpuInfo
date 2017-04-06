#include <QDebug>
#include <QRegularExpression>

#include "datamodel.h"

static QString const CPU_PATTERN_start = "processor";
static QString const CPU_PATTERN_end = "\n\n";
static QString const MODEL_KEY = "key";
static QString const MODEL_VALUE = "value";
static QString const LINE_PATTERN = "(?<key>[^:]*):\\s(?<value>[^\\n]*)\\n";
static QString const CPU_LOGICAL_UNITS = "logical_units";

DataModel::DataModel(DataModel *derived, QObject *parent) : QQmlPropertyMap(derived, parent)
{
    if (mFileReaderThread.isNull())
    {
        mFileReaderThread.reset(new QThread(),
                                 &QObject::deleteLater);

        mFileReader.reset(new FileReader(),
                           &QObject::deleteLater);

        mFileReader.data()->moveToThread(mFileReaderThread.data());

        connect(mFileReaderThread.data(),
                SIGNAL(started()),
                mFileReader.data(),
                SLOT(readData()),
                Qt::DirectConnection);

        connect(mFileReader.data(),
                SIGNAL(finished()),
                mFileReaderThread.data(),
                SLOT(quit()),
                Qt::DirectConnection);

        connect(mFileReader.data(),
                SIGNAL(updateDataStream(QByteArray)),
                derived,
                SLOT(updateDataModel(QByteArray)));

        mFileReaderThread.data()->start();
    }
    else
    {
        qWarning() << __FUNCTION__
                   << "FileReader Thread is already running";
    }
}

void DataModel::updateDataModel(QByteArray datastream)
{
    QList<QByteArray> cpuList;
    qint32 startBlock = 0;
    qint32 endBlock = 0;

    // This while loop seperates the datastream to a list of logical core entries.
    while ((endBlock = datastream.indexOf(CPU_PATTERN_end, startBlock)) != -1)
    {
        qint32 lengthBlock = endBlock - startBlock;
        cpuList.append(datastream.mid(startBlock,
                                      lengthBlock));
        startBlock = datastream.indexOf(CPU_PATTERN_start,
                                        endBlock);
        ++endBlock;
    }

    if (cpuList.size() > 0)
    {
        //insert the overall sum of logical cores in the data model
        this->insert(QString(CPU_LOGICAL_UNITS), QVariant(cpuList.size()));
        for (qint32 j = 0; j< cpuList.size(); ++j)
        {
            QRegularExpression lineColonSeperater(LINE_PATTERN);
            //seperate each line inside a logical core entry and store the information in a key,value pair
            QRegularExpressionMatchIterator seperatedLines = lineColonSeperater.globalMatch(cpuList.at(j));
            while (seperatedLines.hasNext())
            {
                QRegularExpressionMatch seperatedLine = seperatedLines.next();
                QString modelKey = seperatedLine.captured(MODEL_KEY).trimmed().append(QString::number(j));
                QVariant modelValue = seperatedLine.captured(MODEL_VALUE).trimmed();
                //store the key,value pair of each line in the data model
                this->insert(modelKey, modelValue);
            }
        }
    }
    else
    {
        qWarning() << __FUNCTION__
                   << "Zero cores in list";
    }
}

DataModel::~DataModel()
{
    if (mFileReaderThread.data()->isRunning())
    {
        mFileReaderThread.data()->quit();
        mFileReaderThread.data()->wait();
    }
    mFileReaderThread.clear();
    mFileReader.clear();
}
