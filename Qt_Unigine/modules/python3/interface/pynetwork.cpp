/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2017 Inviwo Foundation
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

#include <modules/python3/interface/pynetwork.h>

#include <modules/python3/interface/inviwopy.h>
#include <modules/python3/interface/pyglmtypes.h>

#include <inviwo/core/network/portconnection.h>
#include <inviwo/core/links/propertylink.h>
#include <inviwo/core/network/processornetwork.h>
#include <inviwo/core/ports/port.h>
#include <inviwo/core/ports/inport.h>



namespace py = pybind11;

namespace inviwo {




void exposeNetwork(py::module &m) {
    py::class_<PortConnection>(m, "PortConnection")
        .def(py::init<Outport *, Inport *>())
        .def_property_readonly("inport", &PortConnection::getInport,
                               py::return_value_policy::reference)
        .def_property_readonly("outport", &PortConnection::getOutport,
                               py::return_value_policy::reference);

    py::class_<PropertyLink>(m, "PropertyLink")
        .def(py::init<Property *, Property *>(), py::arg("src"), py::arg("dst"))
        .def_property_readonly("source", &PropertyLink::getSource,
                               py::return_value_policy::reference)
        .def_property_readonly("destination", &PropertyLink::getDestination,
                               py::return_value_policy::reference);

    py::class_<ProcessorNetwork>(m, "ProcessorNetwork")
        .def_property_readonly("processors", &ProcessorNetwork::getProcessors,
                               py::return_value_policy::reference)
        .def("getProcessorByIdentifier", &ProcessorNetwork::getProcessorByIdentifier,
             py::return_value_policy::reference)
        .def("__getattr__",
             [](ProcessorNetwork &po, std::string key) {
                 auto p = po.getProcessorByIdentifier(key);
                 if (auto cp = dynamic_cast<CanvasProcessor *>(p)) {
                     return py::cast(cp);
                 }
                 return py::cast(p);

             },
             py::return_value_policy::reference)
        .def("addProcessor",
             [](ProcessorNetwork *pn, Processor *processor) { pn->addProcessor(processor); })
        .def("removeProcessor",
             [](ProcessorNetwork *pn, Processor *processor) { pn->removeProcessor(processor); })

        .def_property_readonly("connections", &ProcessorNetwork::getConnections,
                               py::return_value_policy::reference)
        .def("addConnection", [&](ProcessorNetwork *on, Outport *sourcePort,
                                  Inport *destPort) { on->addConnection(sourcePort, destPort); },
             py::arg("sourcePort"), py::arg("destPort"))
        .def("addConnection", [&](ProcessorNetwork *on,
                                  PortConnection &connection) { on->addConnection(connection); })
        .def("removeConnection",
             [&](ProcessorNetwork *on, Outport *sourcePort, Inport *destPort) {
                 on->removeConnection(sourcePort, destPort);
             },
             py::arg("sourcePort"), py::arg("destPort"))
        .def("removeConnection",
             [&](ProcessorNetwork *on, PortConnection &connection) {
                 on->removeConnection(connection);
             })

        .def("isConnected", [&](ProcessorNetwork *on, Outport *sourcePort,
                                Inport *destPort) { on->isConnected(sourcePort, destPort); },
             py::arg("sourcePort"), py::arg("destPort"))
        .def("isPortInNetwork", &ProcessorNetwork::isPortInNetwork)
        .def_property_readonly("links", &ProcessorNetwork::getLinks,
                               py::return_value_policy::reference)
        .def("addLink",
             [](ProcessorNetwork *pn, Property *src, Property *dst) { pn->addLink(src, dst); })
        .def("addLink", [](ProcessorNetwork *pn, PropertyLink &link) { pn->addLink(link); })
        .def("removeLink",
             [](ProcessorNetwork *pn, Property *src, Property *dst) { pn->removeLink(src, dst); })

        .def("removeLink",
             [](ProcessorNetwork *pn, Property *src, Property *dst) { pn->removeLink(src, dst); })
        .def("isLinked", [](ProcessorNetwork *pn, PropertyLink &link) { pn->isLinked(link); })
        .def("isLinkedBidirectional", &ProcessorNetwork::isLinkedBidirectional)
        .def("getLinksBetweenProcessors", &ProcessorNetwork::getLinksBetweenProcessors,
             py::return_value_policy::reference)
        .def_property_readonly("canvases", &ProcessorNetwork::getProcessorsByType<CanvasProcessor>,
                               py::return_value_policy::reference)
        .def("getProperty", &ProcessorNetwork::getProperty, py::return_value_policy::reference)
        .def("getPropertiesLinkedTo", &ProcessorNetwork::getPropertiesLinkedTo,
             py::return_value_policy::reference)
        .def("isPropertyInNetwork", &ProcessorNetwork::isPropertyInNetwork)
        .def_property_readonly("version", &ProcessorNetwork::getVersion)
        .def_property_readonly("empty", &ProcessorNetwork::isEmpty)
        .def_property_readonly("invalidating", &ProcessorNetwork::isInvalidating)
        .def_property_readonly("linking", &ProcessorNetwork::isLinking)
        .def("lock", &ProcessorNetwork::lock)
        .def("unlock", &ProcessorNetwork::unlock)
        .def_property_readonly("locked", &ProcessorNetwork::islocked)
        .def_property_readonly("deserializing", &ProcessorNetwork::isDeserializing)

        .def("clear",
             [&](ProcessorNetwork *pn) { pn->getApplication()->getWorkspaceManager()->clear(); })
        .def("save",
             [](ProcessorNetwork *network, std::string filename) {
                 network->getApplication()->getWorkspaceManager()->save(
                     filename, [&](ExceptionContext ec) { throw; });  // is this the correct way of
                                                                      // re throwing (we just want
                                                                      // to pass the exception on to
                                                                      // python)
             })
        .def("load", [](ProcessorNetwork *network, std::string filename) {
            network->clear();
            network->getApplication()->getWorkspaceManager()->load(
                filename, [&](ExceptionContext ec) { throw; });  // is this the correct way of re
                                                                 // throwing (we just want to pass
                                                                 // the exception on to python)
        });

    py::class_<Port>(m, "Port")
        .def_property_readonly("identifier", &Port::getIdentifier)
        .def_property_readonly("processor", &Port::getProcessor, py::return_value_policy::reference)
        .def_property_readonly("classIdentifier", &Port::getClassIdentifier)
        .def_property_readonly("contentInfo", &Port::getContentInfo)
        .def("isConnected", &Port::isConnected)
        .def("isReady", &Port::isReady);

    py::class_<Inport, Port>(m, "Inport")
        .def_property("optional", &Inport::isOptional, &Inport::setOptional)
        .def("canConnectTo", &Inport::canConnectTo)
        .def("connectTo", &Inport::connectTo)
        .def("disconnectFrom", &Inport::disconnectFrom)
        .def("isConnectedTo", &Inport::isConnectedTo)
        .def("getConnectedOutport", &Inport::getConnectedOutport,
             py::return_value_policy::reference)
        .def("getConnectedOutports", &Inport::getConnectedOutports,
             py::return_value_policy::reference)
        .def("getMaxNumberOfConnections", &Inport::getMaxNumberOfConnections)
        .def("getNumberOfConnections", &Inport::getNumberOfConnections)
        .def("getChangedOutports", &Inport::getChangedOutports, py::return_value_policy::reference);

    py::class_<Outport, Port> pyOutport(m, "Outport");
    pyOutport.def("isConnectedTo", &Outport::isConnectedTo);
    pyOutport.def("getConnectedInports", &Outport::getConnectedInports, py::return_value_policy::reference);


    exposeOutport<DataOutport<std::vector<vec2>>>(m, "Vec2");
    exposeOutport<DataOutport<std::vector<vec3>>>(m, "Vec3");
    exposeOutport<DataOutport<std::vector<vec4>>>(m, "Vec4");
    exposeOutport<DataOutport<std::vector<dvec2>>>(m, "dVec2");
    exposeOutport<DataOutport<std::vector<dvec3>>>(m, "dVec3");
    exposeOutport<DataOutport<std::vector<dvec4>>>(m, "dVec4");
    exposeOutport<DataOutport<std::vector<ivec2>>>(m, "iVec2");
    exposeOutport<DataOutport<std::vector<ivec3>>>(m, "iVec3");
    exposeOutport<DataOutport<std::vector<ivec4>>>(m, "iVec4");
    exposeOutport<DataOutport<std::vector<size2_t>>>(m, "Size2t");
    exposeOutport<DataOutport<std::vector<size3_t>>>(m, "Size3t");
    exposeOutport<DataOutport<std::vector<size4_t>>>(m, "Size4t");

   



}
}  // namespace
