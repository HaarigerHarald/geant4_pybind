#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4LogicalBorderSurface.hh>
#include <G4SurfaceProperty.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LogicalBorderSurface(py::module &m)
{
   py::class_<G4LogicalBorderSurface, G4LogicalSurface>(m, "G4LogicalBorderSurface")

      .def(py::init<const G4String &, G4VPhysicalVolume *, G4VPhysicalVolume *, G4SurfaceProperty *>(), py::arg("name"),
           py::arg("vol1"), py::arg("vol2"), py::arg("surfaceProperty"))

      .def(py::self == py::self)
      .def(py::self != py::self)
      .def_static("GetSurface", &G4LogicalBorderSurface::GetSurface, py::arg("vol1"), py::arg("vol2"),
                  py::return_value_policy::reference)

      .def("SetPhysicalVolumes", &G4LogicalBorderSurface::SetPhysicalVolumes, py::arg("vol1"), py::arg("vol2"))
      .def("GetVolume1", &G4LogicalBorderSurface::GetVolume1, py::return_value_policy::reference)
      .def("GetVolume2", &G4LogicalBorderSurface::GetVolume2, py::return_value_policy::reference)
      .def("GetIndex", &G4LogicalBorderSurface::GetIndex)
      .def("SetVolume1", &G4LogicalBorderSurface::SetVolume1, py::arg("vol1"))
      .def("SetVolume2", &G4LogicalBorderSurface::SetVolume2, py::arg("vol2"))
      .def_static("CleanSurfaceTable", &G4LogicalBorderSurface::CleanSurfaceTable)
      .def_static("GetSurfaceTable", &G4LogicalBorderSurface::GetSurfaceTable, py::return_value_policy::reference)
      .def_static("GetNumberOfBorderSurfaces", &G4LogicalBorderSurface::GetNumberOfBorderSurfaces)
      .def_static("DumpInfo", &G4LogicalBorderSurface::DumpInfo);
}
