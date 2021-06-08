#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VSolid.hh>
#include <G4Version.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VSolid : public G4VSolid {
public:
   using G4VSolid::G4VSolid;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4VSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4VSolid, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4VSolid, GetPointOnSurface, ); }

   // TODO Need to override all pure virtual functions
};

void export_G4VSolid(py::module &m)
{
   py::class_<G4VSolid, PyG4VSolid, py::nodelete>(m, "G4VSolid", "solid class")
      //.def(py::init<const G4String&>())

      .def("GetName", &G4VSolid::GetName)
      .def("SetName", &G4VSolid::SetName)
      .def("DumpInfo", &G4VSolid::DumpInfo)
      .def("GetCubicVolume", &G4VSolid::GetCubicVolume)
      .def("GetSurfaceArea", &G4VSolid::GetSurfaceArea)
      .def("GetPointOnSurface", &G4VSolid::GetPointOnSurface);
}
