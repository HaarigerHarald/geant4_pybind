#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4LogicalSkinSurface.hh>
#include <G4SurfaceProperty.hh>
#include <G4LogicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LogicalSkinSurface(py::module &m)
{
   py::class_<G4LogicalSkinSurface, G4LogicalSurface>(m, "G4LogicalSkinSurface")

      .def(py::init<const G4String &, G4LogicalVolume *, G4SurfaceProperty *>(), py::arg("name"), py::arg("vol"),
           py::arg("surfaceProperty"))

      .def(py::self == py::self)
      .def(py::self != py::self)
      .def_static("GetSurface", &G4LogicalSkinSurface::GetSurface, py::arg("vol"), py::return_value_policy::reference)
      .def("GetLogicalVolume", &G4LogicalSkinSurface::GetLogicalVolume, py::return_value_policy::reference)
      .def("SetLogicalVolume", &G4LogicalSkinSurface::SetLogicalVolume, py::arg("vol"))
      .def_static("CleanSurfaceTable", &G4LogicalSkinSurface::CleanSurfaceTable)
      .def_static("GetSurfaceTable", &G4LogicalSkinSurface::GetSurfaceTable, py::return_value_policy::reference)
      .def_static("GetNumberOfSkinSurfaces", &G4LogicalSkinSurface::GetNumberOfSkinSurfaces)
      .def_static("DumpInfo", &G4LogicalSkinSurface::DumpInfo);
}
