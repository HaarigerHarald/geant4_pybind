#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4SmartVoxelProxy.hh>
#include <G4SmartVoxelNode.hh>
#include <G4SmartVoxelHeader.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SmartVoxelProxy(py::module &m)
{
   py::class_<G4SmartVoxelProxy>(m, "G4SmartVoxelProxy")

      .def(py::init<G4SmartVoxelHeader *>(), py::arg("pHeader"))
      .def(py::init<G4SmartVoxelNode *>(), py::arg("pNode"))
      .def("__copy__", [](const G4SmartVoxelProxy &self) { return G4SmartVoxelProxy(self); })
      .def("__deepcopy__", [](const G4SmartVoxelProxy &self, py::dict) { return G4SmartVoxelProxy(self); })
      .def("IsHeader", &G4SmartVoxelProxy::IsHeader)
      .def("IsNode", &G4SmartVoxelProxy::IsNode)
      .def("GetNode", &G4SmartVoxelProxy::GetNode, py::return_value_policy::reference)
      .def("GetHeader", &G4SmartVoxelProxy::GetHeader, py::return_value_policy::reference)
      .def(py::self == py::self);
}
