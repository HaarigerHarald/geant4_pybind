#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UnionSolid.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UnionSolid(py::module &m)
{
   py::class_<G4UnionSolid, G4BooleanSolid, std::unique_ptr<G4UnionSolid, py::nodelete>>(m, "G4UnionSolid",
                                                                                         "union solid class")
      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>())
      .def(py::init<>([](const G4String &pName, G4VSolid *pSolidA, G4VSolid *pSolidB, G4RotationMatrix *rotMatrix,
                         const G4ThreeVector &transVector) {
         owntrans_ptr<G4RotationMatrix>::remove(rotMatrix);
         return G4UnionSolid(pName, pSolidA, pSolidB, rotMatrix, transVector);
      }))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>());
}
