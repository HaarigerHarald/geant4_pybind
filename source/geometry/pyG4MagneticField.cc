#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagneticField.hh>
#include <G4ThreeVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagneticField : G4MagneticField {
public:
   using G4MagneticField::G4MagneticField;

   void GetFieldValue(const G4double Point[4], G4double *Bfield) const override
   {
      py::gil_scoped_acquire gil;
      py::function pyGetFieldValue = py::get_override(static_cast<const G4MagneticField *>(this), "GetFieldValue");

      if (pyGetFieldValue) {
         py::list pyBfield(3);
         py::list pointList(4);
         for (size_t i = 0; i < pyBfield.size(); i++) {
            pyBfield[i] = 0;
         }
         pointList[0]          = Point[0];
         pointList[1]          = Point[1];
         pointList[2]          = Point[2];
         pointList[3]          = Point[3];
         py::object pyretField = pyGetFieldValue(pointList, pyBfield);
         if (py::isinstance<py::list>(pyretField) && ((py::list)pyretField).size() == 3) {
            Bfield[0] = ((py::list)pyretField)[0].cast<G4double>();
            Bfield[1] = ((py::list)pyretField)[1].cast<G4double>();
            Bfield[2] = ((py::list)pyretField)[2].cast<G4double>();
         } else if (pyBfield.size() == 3) {
            Bfield[0] = pyBfield[0].cast<G4double>();
            Bfield[1] = pyBfield[1].cast<G4double>();
            Bfield[2] = pyBfield[2].cast<G4double>();
         } else {
            py::pybind11_fail("\"G4MagneticField::GetFieldValue\" Bfield must have 3 components");
         }
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
