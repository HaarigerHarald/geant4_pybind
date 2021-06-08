#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UniformMagField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UniformMagField(py::module &m)
{
   py::class_<G4UniformMagField, G4Field>(m, "G4UniformMagField", "uniform magnetic field")

      .def(py::init<const G4ThreeVector &>())
      .def(py::init<const G4double, G4double, G4double>())

      .def("SetFieldValue", &G4UniformMagField::SetFieldValue)
      .def("GetConstantFieldValue", &G4UniformMagField::GetConstantFieldValue);
}
