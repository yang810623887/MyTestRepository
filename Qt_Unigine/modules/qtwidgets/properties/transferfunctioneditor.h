/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2017 Inviwo Foundation
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

#ifndef IVW_TRANSFERFUNCTIONEDITOR_H
#define IVW_TRANSFERFUNCTIONEDITOR_H

#include <modules/qtwidgets/qtwidgetsmoduledefine.h>
#include <inviwo/core/datastructures/datamapper.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QGraphicsScene>
#include <QPointF>
#include <warn/pop>

#include <vector>

class QGraphicsView;
class QGraphicsPathItem;
class QColorDialog;

namespace inviwo {

class TransferFunction;
class TransferFunctionProperty;
class TransferFunctionEditorControlPoint;
class TransferFunctionControlPointConnection;
class TransferFunctionDataPoint;

class IVW_MODULE_QTWIDGETS_API TransferFunctionEditor : public QGraphicsScene {
#include <warn/push>
#include <warn/ignore/all>
    Q_OBJECT
#include <warn/pop>
public:
    TransferFunctionEditor(TransferFunctionProperty* tfProperty, QWidget* parent = nullptr);
    virtual ~TransferFunctionEditor();

    float getZoomRangeXMin() const;
    void setZoomRangeXMin(float min);
    float getZoomRangeXMax() const;
    void setZoomRangeXMax(float max);
    float getZoomRangeYMin() const;
    void setZoomRangeYMin(float min);

    float getZoomRangeYMax() const;
    void setZoomRangeYMax(float max);
    void updateConnections();
    int getMoveMode() const;
    void setMoveMode(int i);

    virtual void onControlPointAdded(TransferFunctionDataPoint* p);
    virtual void onControlPointRemoved(TransferFunctionDataPoint* p);
    virtual void onControlPointChanged(const TransferFunctionDataPoint* p);

    /**
     * \brief Get the display size of the control points.
     * @see TransferFunctionEditorControlPoint::setSize
     */
    float getControlPointSize() const { return controlPointSize_; }
    /**
     * \brief Set the display size of the control points.
     *
     * @see TransferFunctionEditorControlPoint::setSize
     * @param val Display size
     */
    void setControlPointSize(float val);

    void setPointColor(const QColor& color);

signals:
    void colorChanged(const QColor& color);

public slots:
    void resetTransferFunction();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* e);
    void keyPressEvent(QKeyEvent* keyEvent);

    /**
     * \brief Adds a new control point at the event position
     *
     * Adds a new control point the the points_ array, adds a new line item to the lines_ array,
     * sorts the points_ array and updates the line items to go to and from the correct points.
     * Runs CalcTransferValues to update the TransferFunction data Image
     */
    void addControlPoint(QPointF pos);
    void addControlPoint(QPointF pos, vec4 color);

    void removeControlPoint(TransferFunctionEditorControlPoint* p);

    TransferFunctionEditorControlPoint* getControlPointGraphicsItemAt(const QPointF pos) const;

private:
    void setColorDialogColor(const QColor& c);

    float controlPointSize_ = 15.f;  ///< Size of control points

    float zoomRangeXMin_;
    float zoomRangeXMax_;
    float zoomRangeYMin_;
    float zoomRangeYMax_;

    TransferFunction* transferFunction_;  ///< Pointer to widget's member variable

    using PointVec = std::vector<TransferFunctionEditorControlPoint*>;
    using ConnectionVec = std::vector<TransferFunctionControlPointConnection*>;
    PointVec points_;
    ConnectionVec connections_;
    QList<QGraphicsItem*>
        selectedItemsAtPress_;  // The items selected when user pressed mouse button.
    bool mouseDrag_;
    bool mouseMovedSincePress_ = false;  // Mouse moved since click
    bool mouseDoubleClick_ = false;
    DataMapper dataMap_;

    std::vector<std::vector<TransferFunctionEditorControlPoint*> > groups_;
    int moveMode_;

    std::unique_ptr<QColorDialog> colorDialog_;
};

}  // namespace inviwo

#endif  // IVW_TRANSFERFUNCTIONEDITOR_H