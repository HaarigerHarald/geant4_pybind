#include <pybind11/pybind11.h>

#include <G4MagneticField.hh>
#include <G4ThreeVector.hh>

#include "typecast.hh"

namespace py = pybind11;

class PyG4MagneticField : G4MagneticField {
public:
   using G4MagneticField::G4MagneticField;

   void GetFieldValue(const G4double Point[4], G4double *Bfield) const override
   {
      py::gil_scoped_acquire gil;
      py::function           pyGetFieldValue = py::get_override(this, "GetFieldValue");

      if (pyGetFieldValue) {
         G4ThreeVector bfield =
            pyGetFieldValue(G4ThreeVector(Point[0], Point[1], Point[2]), Point[3]).cast<G4ThreeVector>();
         Bfield[0] = bfield.x();
         Bfield[1] = bfield.y();
         Bfield[2] = bfield.z();
      } else {
         py::pybind11_fail("Tried to call pure virtual function \"G4MagneticField::GetFieldValue\"");
      }
   }
};

void export_G4MagneticField(py::module &m)
{

   py::class_<G4MagneticField, G4Field, PyG4MagneticField, std::unique_ptr<G4MagneticField>>(
      m, "G4MagneticField", "base class of magnetic field")
      .def(py::init<>())

      .def("DoesFieldChangeEnergy", &G4MagneticField::DoesFieldChangeEnergy)
      .def("GetFieldValue", &G4MagneticField::GetFieldValue);
}
