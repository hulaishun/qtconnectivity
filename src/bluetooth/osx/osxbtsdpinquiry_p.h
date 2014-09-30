/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#ifndef OSXBTSDPINQUIRY_H
#define OSXBTSDPINQUIRY_H

#include "qbluetoothaddress.h"
#include "qbluetoothuuid.h"

#include <QtCore/qglobal.h>
#include <QtCore/qlist.h>

#include <Foundation/Foundation.h>

@class QT_MANGLE_NAMESPACE(OSXBTSDPInquiry);
@class IOBluetoothSDPServiceRecord;
@class IOBluetoothSDPDataElement;
@class IOBluetoothDevice;

QT_BEGIN_NAMESPACE

class QBluetoothServiceInfo;
class QVariant;

namespace OSXBluetooth {

class SDPInquiryDelegate {
public:
    typedef QT_MANGLE_NAMESPACE(OSXBTSDPInquiry) ObjCServiceInquiry;

    virtual ~SDPInquiryDelegate();

    virtual void SDPInquiryFinished(IOBluetoothDevice *device) = 0;
    virtual void SDPInquiryError(IOBluetoothDevice *device, IOReturn errorCode) = 0;
};

void extract_service_record(IOBluetoothSDPServiceRecord *record, QBluetoothServiceInfo &serviceInfo);
QVariant extract_attribute_value(IOBluetoothSDPDataElement *dataElement);
QList<QBluetoothUuid> extract_services_uuids(IOBluetoothDevice *device);

}

QT_END_NAMESPACE

@interface QT_MANGLE_NAMESPACE(OSXBTSDPInquiry) : NSObject
{
    QT_PREPEND_NAMESPACE(OSXBluetooth::SDPInquiryDelegate) *delegate;
    IOBluetoothDevice *device;
    bool isActive;
}

- (id)initWithDelegate:(QT_PREPEND_NAMESPACE(OSXBluetooth::SDPInquiryDelegate) *)aDelegate;
- (void)dealloc;

- (IOReturn)performSDPQueryWithDevice:(const QBluetoothAddress &)address;
- (IOReturn)performSDPQueryWithDevice:(const QBluetoothAddress &)address
                              filters:(const QList<QBluetoothUuid> &)filters;

- (void)stopSDPQuery;

- (void)sdpQueryComplete:(IOBluetoothDevice *)aDevice status:(IOReturn)status;

@end

#endif