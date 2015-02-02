/*
 * Copyright (C) 2015 Brian Matherly <code@brianmatherly.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with consumer library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <QtTest>

#include <mlt++/Mlt.h>
using namespace Mlt;

class TestFrame: public QObject
{
    Q_OBJECT

public:
    TestFrame() {}

private Q_SLOTS:
    void FrameConstructorAddsReference()
    {
        mlt_frame frame = mlt_frame_init(NULL);
        QCOMPARE(mlt_properties_ref_count( MLT_FRAME_PROPERTIES(frame) ), 1);
        Frame f(frame);
        QCOMPARE(f.ref_count(), 2);
        mlt_frame_close(frame);
    }

    void CopyConstructorAddsReference()
    {
        mlt_frame frame = mlt_frame_init(NULL);
        QCOMPARE(mlt_properties_ref_count( MLT_FRAME_PROPERTIES(frame) ), 1);
        Frame f1(frame);
        QCOMPARE(f1.ref_count(), 2);
        Frame f2(f1);
        QCOMPARE(f1.ref_count(), 3);
        mlt_frame_close(frame);
    }

    void DestructionRemovesReference()
    {
        mlt_frame frame = mlt_frame_init(NULL);
        QCOMPARE(mlt_properties_ref_count( MLT_FRAME_PROPERTIES(frame) ), 1);
        Frame f1(frame);
        QCOMPARE(f1.ref_count(), 2);
        Frame* f2 = new Frame(f1);
        QCOMPARE(f2->ref_count(), 3);
        delete f2;
        QCOMPARE(f1.ref_count(), 2);
        mlt_frame_close(frame);
    }
};

QTEST_APPLESS_MAIN(TestFrame)

#include "test_frame.moc"
