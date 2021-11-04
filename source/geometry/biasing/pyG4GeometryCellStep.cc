#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryCellStep.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryCellStep(py::module &m)
{
   py::class_<G4GeometryCellStep>(m, "G4GeometryCellStep")

      .def(py::init<const G4GeometryCell &, const G4GeometryCell &>(), py::arg("preCell"), py::arg("postCell"))
      .def("__copy__", [](const G4GeometryCellStep &self) { return G4GeometryCellStep(self); })
      .def("__deepcopy__", [](const G4GeometryCellStep &self, py::dict) { return G4GeometryCellStep(self); })
      .def("GetPreGeometryCell", &G4GeometryCellStep::GetPreGeometryCell)
      .def("GetPostGeometryCell", &G4GeometryCellStep::GetPostGeometryCell)
      .def("GetCrossBoundary", &G4GeometryCellStep::GetCrossBoundary)
      .def("SetPreGeometryCell", &G4GeometryCellStep::SetPreGeometryCell, py::arg("preCell"))
      .def("SetPostGeometryCell", &G4GeometryCellStep::SetPostGeometryCell, py::arg("postCell"))
      .def("SetCrossBoundary", &G4GeometryCellStep::SetCrossBoundary, py::arg("b"));
}
