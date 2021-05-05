#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UniformElectricField.hh>
#include <G4UniformGravityField.hh>
#include <G4ThreeVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UniformFields(py::module &m)
{
   py::class_<G4UniformElectricField, G4ElectricField, std::unique_ptr<G4UniformElectricField>>(
      m, "G4UniformElectricField")
      .def(py::init<const G4ThreeVector &>(), py::arg("FieldVector"))
      .def(py::init<G4double, G4double, G4double>(), py::arg("vField"), py::arg("vTheta"), py::arg("vPhi"))

      //.def("GetFieldValue", &G4UniformElectricField::GetFieldValue)
      ;

   py::class_<G4UniformGravityField, G4Field, std::unique_ptr<G4UniformGravityField>>(m, "G4UniformGravityField")
      .def(py::init<const G4ThreeVector &>(), py::arg("FieldVector"))
      .def(py::init<const G4double>(), py::arg("gy") = -9.81 * CLHEP::m / CLHEP::s / CLHEP::s)

      //.def("GetFieldValue", &G4UniformGravityField::GetFieldValue);
      .def("DoesFieldChangeEnergy", &G4UniformGravityField::DoesFieldChangeEnergy);
}
