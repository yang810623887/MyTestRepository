/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2017 Inviwo Foundation
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

#include "basisproperty.h"

namespace inviwo {

PropertyClassIdentifier(BasisProperty, "org.inviwo.VolumeBasisProperty");

BasisProperty::BasisProperty(std::string identifier, std::string displayName,
                                         InvalidationLevel invalidationLevel,
                                         PropertySemantics semantics)
    : CompositeProperty(identifier, displayName, invalidationLevel, semantics)
    , overRideDefaults_("override", "Override", false)
    , a_("a", "A", vec3(1.0f, 0.0f, 0.0f), vec3(-10.0f), vec3(10.0f))
    , b_("b", "B", vec3(0.0f, 1.0f, 0.0f), vec3(-10.0f), vec3(10.0f))
    , c_("c", "C", vec3(0.0f, 0.0f, 1.0f), vec3(-10.0f), vec3(10.0f))
    , offset_("offset", "Offset", vec3(0.0f), vec3(-10.0f), vec3(10.0f))

    , overrideA_("overrideA", "A (override)", vec3(1.0f, 0.0f, 0.0f), vec3(-10.0f), vec3(10.0f))
    , overrideB_("overrideB", "B (override)", vec3(0.0f, 1.0f, 0.0f), vec3(-10.0f), vec3(10.0f))
    , overrideC_("overrideC", "C (override)", vec3(0.0f, 0.0f, 1.0f), vec3(-10.0f), vec3(10.0f))
    , overrideOffset_("overrideOffset", "Offset (override)", vec3(0.0f), vec3(-10.0f), vec3(10.0f)) {
    a_.setReadOnly(true);
    a_.setSerializationMode(PropertySerializationMode::None);
    b_.setReadOnly(true);
    b_.setSerializationMode(PropertySerializationMode::None);
    c_.setReadOnly(true);
    c_.setSerializationMode(PropertySerializationMode::None);
    offset_.setReadOnly(true);
    offset_.setSerializationMode(PropertySerializationMode::None);

    overrideA_.setSerializationMode(PropertySerializationMode::All);
    overrideA_.setVisible(false);
    overrideB_.setSerializationMode(PropertySerializationMode::All);
    overrideB_.setVisible(false);
    overrideC_.setSerializationMode(PropertySerializationMode::All);
    overrideC_.setVisible(false);
    overrideOffset_.setSerializationMode(PropertySerializationMode::All);
    overrideOffset_.setVisible(false);

    addProperty(overRideDefaults_);
    addProperty(a_);
    addProperty(b_);
    addProperty(c_);
    addProperty(offset_);
    addProperty(overrideA_);
    addProperty(overrideB_);
    addProperty(overrideC_);
    addProperty(overrideOffset_);

    overRideDefaults_.onChange([this]() { onOverrideChange(); });
}

BasisProperty::BasisProperty(const BasisProperty& rhs)
    : CompositeProperty(rhs)
    , overRideDefaults_(rhs.overRideDefaults_)
    , a_(rhs.a_)
    , b_(rhs.b_)
    , c_(rhs.c_)
    , offset_(rhs.offset_)
    , overrideA_(rhs.overrideB_)
    , overrideB_(rhs.overrideB_)
    , overrideC_(rhs.overrideC_)
    , overrideOffset_(rhs.overrideOffset_) {
    addProperty(overRideDefaults_);
    addProperty(a_);
    addProperty(b_);
    addProperty(c_);
    addProperty(offset_);
    addProperty(overrideA_);
    addProperty(overrideB_);
    addProperty(overrideC_);
    addProperty(overrideOffset_);

    overRideDefaults_.onChange([this]() { onOverrideChange(); });
}

BasisProperty* BasisProperty::clone() const {
    return new BasisProperty(*this);
}

void BasisProperty::updateForNewEntity(const SpatialEntity<3>& volume, bool deserialize) {
    // Set basis properties to the values from the new volume
    // Heuristics: Use the same min/max of basis vector, 
    // since basis is often zero in two dimensions, i.e. when axis-aligned and orthogonal.

    // Set min/max range to be an order of magnitude larger
    const auto boundsScale = 5.f;
    const auto incrementScale = 0.1f;

    auto minBounds = volume.getModelMatrix() - boundsScale* glm::abs(volume.getModelMatrix());
    auto maxBounds = volume.getModelMatrix() + boundsScale* glm::abs(volume.getModelMatrix());
    // Min/max for basis vectors (cannot do compMin/compMax on matrices)
    auto minBound = glm::compMin(minBounds[0]);
    for (auto i = 1; i < 3; i++) { minBound = glm::min(minBound, glm::compMin(minBounds[i])); }
    auto maxBound = glm::compMax(maxBounds[0]);
    for (auto i = 1; i < 3; i++) { maxBound = glm::max(maxBound, glm::compMax(maxBounds[i])); }
    auto increment = incrementScale*glm::abs(maxBound - minBound);

    // Min/max/increment for offset
    auto minOffset = glm::compMin(minBounds[3]);
    auto maxOffset = glm::compMax(maxBounds[3]);
    auto offsetIncrement = incrementScale*glm::abs(maxOffset - minOffset);

    a_.set(volume.getBasis()[0], vec3(minBound), vec3(maxBound), vec3(increment));
    b_.set(volume.getBasis()[1], vec3(minBound), vec3(maxBound), vec3(increment));
    c_.set(volume.getBasis()[2], vec3(minBound), vec3(maxBound), vec3(increment));
    offset_.set(volume.getOffset(), vec3(minOffset), vec3(maxOffset), vec3(offsetIncrement));

    a_.setCurrentStateAsDefault();
    b_.setCurrentStateAsDefault();
    c_.setCurrentStateAsDefault();
    offset_.setCurrentStateAsDefault();

    if (deserialize) {
        Property::setStateAsDefault(overrideA_, volume.getBasis()[0]);
        Property::setStateAsDefault(overrideB_, volume.getBasis()[1]);
        Property::setStateAsDefault(overrideC_, volume.getBasis()[2]);
        Property::setStateAsDefault(overrideOffset_, volume.getOffset());
    } else {
        overrideA_.set(volume.getBasis()[0]);
        overrideB_.set(volume.getBasis()[1]);
        overrideC_.set(volume.getBasis()[2]);
        overrideOffset_.set(volume.getOffset());
        overrideA_.setCurrentStateAsDefault();
        overrideB_.setCurrentStateAsDefault();
        overrideC_.setCurrentStateAsDefault();
        overrideOffset_.setCurrentStateAsDefault();
    }
}

void BasisProperty::onOverrideChange() {
    if (overRideDefaults_) {
        a_.setVisible(false);
        b_.setVisible(false);
        c_.setVisible(false);
        offset_.setVisible(false);

        overrideA_.setVisible(true);
        overrideB_.setVisible(true);
        overrideC_.setVisible(true);
        overrideOffset_.setVisible(true);
    } else {
        overrideA_.setVisible(false);
        overrideB_.setVisible(false);
        overrideC_.setVisible(false);
        overrideOffset_.setVisible(false);

        a_.setVisible(true);
        b_.setVisible(true);
        c_.setVisible(true);
        offset_.setVisible(true);
    }
}

BasisProperty& BasisProperty::operator=(const BasisProperty& that) {
    if (this != &that) {
        CompositeProperty::operator=(that);
        overRideDefaults_ = that.overRideDefaults_;
        a_ = that.a_;
        b_ = that.b_;
        c_ = that.c_;
        offset_ = that.offset_;
        overrideA_ = that.overrideB_;
        overrideB_ = that.overrideB_;
        overrideC_ = that.overrideC_;
        overrideOffset_ = that.overrideOffset_;
    }
    return *this;
}

mat4 BasisProperty::getBasisAndOffset() const {
    if (overRideDefaults_) {
        vec4 offset = vec4(overrideOffset_.get(), 1.0f);
        mat3 basis(overrideA_, overrideB_, overrideC_);
        mat4 basisAndOffset(basis);
        basisAndOffset[3] = offset;
        return basisAndOffset;
    } else {
        vec4 offset = vec4(offset_.get(), 1.0f);
        mat3 basis(a_, b_, c_);
        mat4 basisAndOffset(basis);
        basisAndOffset[3] = offset;
        return basisAndOffset;
    }

}

void BasisProperty::updateEntity(SpatialEntity<3>& volume) {
    volume.setModelMatrix(getBasisAndOffset());
}

}  // namespace
