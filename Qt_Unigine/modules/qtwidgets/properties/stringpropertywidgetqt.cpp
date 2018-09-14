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

#include <modules/qtwidgets/properties/stringpropertywidgetqt.h>
#include <modules/qtwidgets/properties/compositepropertywidgetqt.h>
#include <inviwo/core/properties/stringproperty.h>
#include <modules/qtwidgets/editablelabelqt.h>
#include <modules/qtwidgets/lineeditqt.h>
#include <modules/qtwidgets/inviwoqtutils.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QSignalBlocker>
#include <warn/pop>


namespace inviwo {

StringPropertyWidgetQt::StringPropertyWidgetQt(StringProperty* property)
    : PropertyWidgetQt(property)
    , property_(property)
    , lineEdit_{new LineEditQt()}
    , label_{new EditableLabelQt(this, property_)} {

    QHBoxLayout* hLayout = new QHBoxLayout();
    setSpacingAndMargins(hLayout);
    setLayout(hLayout);
    hLayout->addWidget(label_);

    if (property_->getSemantics().getString() == "Password") {
        lineEdit_->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    }

    QSizePolicy sp = lineEdit_->sizePolicy();
    sp.setHorizontalStretch(3);
    lineEdit_->setSizePolicy(sp);

    hLayout->addWidget(lineEdit_);

    connect(lineEdit_, &LineEditQt::editingFinished, this,
            &StringPropertyWidgetQt::setPropertyValue);
    connect(lineEdit_, &LineEditQt::editingCanceled, [this]() {
        // undo textual changes by resetting the contents of the line edit
        QSignalBlocker blocker(lineEdit_);
        updateFromProperty();
        lineEdit_->clearFocus();
    });

    updateFromProperty();
}

void StringPropertyWidgetQt::setPropertyValue() {
    std::string valueStr = utilqt::fromQString(lineEdit_->text());
    property_->setInitiatingWidget(this);
    property_->set(valueStr);
    property_->clearInitiatingWidget();
}

void StringPropertyWidgetQt::updateFromProperty() {
    QSignalBlocker blocker(lineEdit_);
    lineEdit_->setText(utilqt::toQString(property_->get()));
    lineEdit_->setCursorPosition(0);
}

} // namespace inviwo
