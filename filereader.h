//!  CPU Filereader.
/*!
  This class is reads the information of the generated proc file.
  It reads the cpu information periodically. If new data is ready it emits a signal updateDataStream.
*/

#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>


class FileReader : public QObject
{
    Q_OBJECT
public:
    //! Constructor of the file reader.
    /*!
      The constructor starts a timer to read the file in an interval.
    */
    explicit FileReader(QObject *parent = 0);
    //! Destructor of the file reader.
    /*!
      The destructor emits a signal to quit the file reader thread.
    */
    ~FileReader();

signals:
    //! This signal is emitted after a new datastream of
    //! CPU information is available
    /*!
      \param fileDatastream stores the new file data
    */
    void updateDataStream(QByteArray fileDatastream);
    //! This signal is emitted to quit the file reader thread
    void finished();

public slots:
    //! This slot is called by the timer to read new data on a periodic time
    void readData();

private:
    //! This function opens the file and reads the data.
    /*!
      \param fileDatastream stores the new file data
    */
    bool readFile(QByteArray &fileDatastream);
    QSharedPointer<QTimer> mReadFileTimer; /**<this member is the timer to read the file in a intervall*/
};

#endif // FILEREADER_H
