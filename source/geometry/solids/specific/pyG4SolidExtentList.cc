#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SolidExtentList.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SolidExtentList(py::module &m)
{
   py::class_<G4SolidExtentList>(m, "G4SolidExtentList")

      .def(py::init<>())
      .def(py::init<const EAxis, const G4VoxelLimits &>(), py::arg("targetAxis"), py::arg("voxelLimits"))
      .def("__copy__", [](const G4SolidExtentList &self) { return G4SolidExtentList(self); })
      .def("__deepcopy__", [](const G4SolidExtentList &self, py::dict) { return G4SolidExtentList(self); })
      .def("AddSurface", &G4SolidExtentList::AddSurface, py::arg("surface"))
      .def("GetExtent", &G4SolidExtentList::GetExtent, py::arg("min"), py::arg("max"));
}
