#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DrawVoxels.hh>
#include <G4AttValue.hh>
#include <G4AttDef.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4LogicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DrawVoxels(py::module &m)
{
   py::class_<G4DrawVoxels>(m, "G4DrawVoxels")

      .def(py::init<>())
      .def("DrawVoxels", &G4DrawVoxels::DrawVoxels, py::arg("lv"))
      .def("CreatePlacedPolyhedra", &G4DrawVoxels::CreatePlacedPolyhedra, py::return_value_policy::reference)
      .def("SetVoxelsVisAttributes", &G4DrawVoxels::SetVoxelsVisAttributes)
      .def("SetBoundingBoxVisAttributes", &G4DrawVoxels::SetBoundingBoxVisAttributes);
}
