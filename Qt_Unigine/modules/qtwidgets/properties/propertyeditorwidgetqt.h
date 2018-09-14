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

#ifndef IVW_PROPERTYEDITORWIDGETQT_H
#define IVW_PROPERTYEDITORWIDGETQT_H

#include <modules/qtwidgets/qtwidgetsmoduledefine.h>
#include <modules/qtwidgets/inviwodockwidget.h>

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/properties/propertywidget.h>


class QResizeEvent;
class QShowEvent;
class QCloseEvent;
class QMoveEvent;

namespace inviwo {

// PropertyEditorWidget owned by PropertyWidget
class IVW_MODULE_QTWIDGETS_API PropertyEditorWidgetQt : public InviwoDockWidget,
                                                        public PropertyEditorWidget {
public:
    PropertyEditorWidgetQt(Property *property, std::string widgetName, QWidget *parent);
    virtual ~PropertyEditorWidgetQt();

    virtual void setVisibility(bool visible) override;
    virtual void setDimensions(const ivec2& dimensions) override;
    virtual void setPosition(const ivec2& pos) override;
    virtual void setDockStatus(PropertyEditorWidgetDockStatus dockStatus) override;
    virtual void setSticky(bool sticky) override;

    virtual bool isVisible() const override;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void closeEvent(QCloseEvent *) override;
    virtual void moveEvent(QMoveEvent *event) override;
};

} // namespace inviwo

#endif // IVW_PROPERTYEDITORWIDGETQT_H
