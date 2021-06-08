#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SubtractionSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SubtractionSolid(py::module &m)
{
   py::class_<G4SubtractionSolid, G4BooleanSolid, py::nodelete>(m, "G4SubtractionSolid", "subtraction solid class")

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>())
      .def(py::init<>([](const G4String &pName, G4VSolid *pSolidA, G4VSolid *pSolidB,
                         py::disown_ptr<G4RotationMatrix> rotMatrix, const G4ThreeVector &transVector) {
         return G4SubtractionSolid(pName, pSolidA, pSolidB, rotMatrix, transVector);
      }))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>());
}
