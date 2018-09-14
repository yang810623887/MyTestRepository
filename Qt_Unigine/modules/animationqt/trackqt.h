/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2016-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_TRACKQT_H
#define IVW_TRACKQT_H

#include <modules/animationqt/animationqtmoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <modules/animation/datastructures/trackobserver.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QGraphicsItem>
#include <warn/pop>

namespace inviwo {

namespace animation {

class Track;
class KeyframeSequenceQt;

class IVW_MODULE_ANIMATIONQT_API TrackQt : public QGraphicsItem, public TrackObserver {
public:
    TrackQt(Track& track);
    virtual ~TrackQt();
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* options,
                       QWidget* widget) override;

    Track& getTrack(); 
    const Track& getTrack() const; 
protected:
    virtual QRectF boundingRect() const override;

    virtual void onKeyframeSequenceAdded(Track* t, KeyframeSequence* s) override;
    virtual void onKeyframeSequenceRemoved(Track* t, KeyframeSequence* s) override;

    Track& track_;
    std::vector<std::unique_ptr<KeyframeSequenceQt>> sequences_;
};

} // namespace

} // namespace

#endif // IVW_TRACKQT_H

