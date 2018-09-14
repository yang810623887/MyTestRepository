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

/** \ Widget for containing the TransferFunctionEditor QGraphicsScene
 *       Widget that contains the TransferFunctionEditor and the painted representation
 */

#ifndef IVW_TRANSFERFUNCTIONPROPERTYDIALOG_H
#define IVW_TRANSFERFUNCTIONPROPERTYDIALOG_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/properties/transferfunctionproperty.h>
#include <modules/qtwidgets/properties/transferfunctioneditor.h>
#include <modules/qtwidgets/properties/transferfunctioneditorview.h>
#include <modules/qtwidgets/properties/ordinalminmaxpropertywidgetqt.h>
#include <modules/qtwidgets/properties/propertyeditorwidgetqt.h>
#include <modules/qtwidgets/properties/optionpropertywidgetqt.h>
#include <inviwo/core/properties/propertywidget.h>
#include <inviwo/core/util/observer.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QGradientStops>
#include <warn/pop>

class QPushButton;
class QComboBox;
class QLabel;
class QPixmap;
class QResizeEvent;
class QShowEvent;

namespace inviwo {

class ColorWheel;
class RangeSliderQt;
class TransferFunctionPropertyWidgetQt;

class IVW_MODULE_QTWIDGETS_API TransferFunctionPropertyDialog : public PropertyEditorWidgetQt,
                                                                public TransferFunctionObserver {
#include <warn/push>
#include <warn/ignore/all>
    Q_OBJECT
#include <warn/pop>

public:
    TransferFunctionPropertyDialog(TransferFunctionProperty* property, QWidget* parent);
    ~TransferFunctionPropertyDialog();

    void updateFromProperty();
    TransferFunctionEditorView* getEditorView() const;

    virtual void onControlPointAdded(TransferFunctionDataPoint* p);
    virtual void onControlPointRemoved(TransferFunctionDataPoint* p);
    virtual void onControlPointChanged(const TransferFunctionDataPoint* p);

public slots:
    void changeMask(int maskMin, int maskMax);

    void changeVerticalZoom(int zoomMin, int zoomMax);
    void changeHorizontalZoom(int zoomMin, int zoomMax);

    void importTransferFunction();
    void exportTransferFunction();
    void showHistogram(int type);
    void changeMoveMode(int i);

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void showEvent(QShowEvent*);

private:
    const int sliderRange_;

    std::unique_ptr<ColorWheel> colorWheel_;

    // Pointer to property, for get and invalidation in the widget
    TransferFunctionProperty* tfProperty_;
    
    // TransferFunctionEditor inherited from QGraphicsScene
    std::unique_ptr<TransferFunctionEditor> tfEditor_;
    
    TransferFunctionEditorView* tfEditorView_;  ///< View that contains the editor
    QPushButton* btnClearTF_;
    QPushButton* btnImportTF_;
    QPushButton* btnExportTF_;
    QComboBox* chkShowHistogram_;

    QComboBox* pointMoveMode_;

    QLabel* tfPreview_;  ///< View that contains the scene for the painted transfer function
    std::unique_ptr<QPixmap> tfPixmap_;

    QLinearGradient gradient_;

    RangeSliderQt* zoomVSlider_;
    RangeSliderQt* zoomHSlider_;
    RangeSliderQt* maskSlider_;

    void generateWidget();
    void updateTFPreview();
};

}  // namespace

#endif  // IVW_TRANSFERFUNCTIONPROPERTYDIALOG_H
