#include <pybind11/pybind11.h>

#include <G4SubtractionSolid.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4SubtractionSolid(py::module &m)
{
   py::class_<G4SubtractionSolid, G4BooleanSolid, std::unique_ptr<G4SubtractionSolid, py::nodelete>>(
      m, "G4SubtractionSolid", "subtraction solid class")

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>())
      .def(py::init<>([](const G4String &pName, G4VSolid *pSolidA, G4VSolid *pSolidB, G4RotationMatrix *rotMatrix,
                         const G4ThreeVector &transVector) {
         owntrans_ptr<G4RotationMatrix>::remove(rotMatrix);
         return G4SubtractionSolid(pName, pSolidA, pSolidB, rotMatrix, transVector);
      }))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>());
}
