#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4SmartVoxelNode.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SmartVoxelNode(py::module &m)
{
   py::class_<G4SmartVoxelNode>(m, "G4SmartVoxelNode")

      .def(py::init<G4int>(), py::arg("pSlice") = 0)
      .def("__copy__", [](const G4SmartVoxelNode &self) { return G4SmartVoxelNode(self); })
      .def("__deepcopy__", [](const G4SmartVoxelNode &self, py::dict) { return G4SmartVoxelNode(self); })
      .def("GetVolume", &G4SmartVoxelNode::GetVolume, py::arg("pVolumeNo"))
      .def("Insert", &G4SmartVoxelNode::Insert, py::arg("pVolumeNo"))
      .def("GetNoContained", &G4SmartVoxelNode::GetNoContained)
      .def("GetCapacity", &G4SmartVoxelNode::GetCapacity)
      .def("Reserve", &G4SmartVoxelNode::Reserve, py::arg("noSlices"))
      .def("Shrink", &G4SmartVoxelNode::Shrink)
      .def("GetMaxEquivalentSliceNo", &G4SmartVoxelNode::GetMaxEquivalentSliceNo)
      .def("SetMaxEquivalentSliceNo", &G4SmartVoxelNode::SetMaxEquivalentSliceNo, py::arg("pMax"))
      .def("GetMinEquivalentSliceNo", &G4SmartVoxelNode::GetMinEquivalentSliceNo)
      .def("SetMinEquivalentSliceNo", &G4SmartVoxelNode::SetMinEquivalentSliceNo, py::arg("pMin"))
      .def(py::self == py::self);
}
