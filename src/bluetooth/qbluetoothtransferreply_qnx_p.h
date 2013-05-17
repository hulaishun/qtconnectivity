/***************************************************************************
**
** Copyright (C) 2013 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QBLUETOOTHTRANSFERREPLY_QNX_P_H
#define QBLUETOOTHTRANSFERREPLY_QNX_P_H

#include <QtCore/QIODevice>

#include <qbluetoothtransferrequest.h>
#include <qbluetoothtransfermanager.h>

#include "qbluetoothtransferreply.h"

#include <QTemporaryFile>
#include <QSocketNotifier>

#include "qnx/ppshelpers_p.h"

QT_BEGIN_NAMESPACE_BLUETOOTH

class Q_BLUETOOTH_EXPORT QBluetoothTransferReplyQnx : public QBluetoothTransferReply
{
    Q_OBJECT

public:
    explicit QBluetoothTransferReplyQnx(QIODevice *input, const QBluetoothTransferRequest &request,
                                        QObject *parent = 0);
    ~QBluetoothTransferReplyQnx();

    bool isFinished() const;
    bool isRunning() const;

    QBluetoothTransferReply::TransferError error() const;
    QString errorString() const;

private Q_SLOTS:
    void controlReply(ppsResult result);
    void controlEvent(ppsResult result);
    void copyDone();
    bool start();

private:
    void startOPP(QString filename);
    QTemporaryFile *tempfile;
    QIODevice *source;

    bool m_running;
    bool m_finished;

    QBluetoothTransferReply::TransferError m_error;
    QString m_errorStr;

    //QString m_agent_path;

    static bool copyToTempFile(QIODevice *to, QIODevice *from);

public slots:
    void abort();
};

QT_END_NAMESPACE_BLUETOOTH

#endif // QBLUETOOTHTRANSFERREPLY_QNX_P_H
