//!  CPU Datamodel.
/*!
  This class is the representation of the correspondending
  datamodel. That datamodel is used for the CPU data in the QML Views.
  It starts a thread to read the cpu information in a file.
*/

#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QThread>
#include <QObject>
#include <QSharedPointer>
#include <QQmlPropertyMap>

#include "filereader.h"

class DataModel : public QQmlPropertyMap
{
    Q_OBJECT
public:
    //! Constructor of the datamodel.
    /*!
      The constructor starts a thread to read the cpu data in a file.
      \param derived is necessary to ensure that properties of the derived class are accessible.
      \param parent parent object
    */
    explicit DataModel(DataModel *derived, QObject *parent=0);
    //! Destructor of the datamodel.
    /*!
      The destructor stops the thread and clears the pointer of the thread.
    */
    ~DataModel();

public slots:
    //! This slot is called to process new cpu information.
    /*!
      \param datastream stores the data update
    */
    void updateDataModel(QByteArray datastream);

private:
    QSharedPointer<FileReader> mFileReader; /**<this member reads the file*/
    QSharedPointer<QThread> mFileReaderThread; /**<this member is the thread to read the file*/
};

#endif // DATAMODEL_H
