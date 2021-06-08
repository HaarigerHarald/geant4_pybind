#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ElectroMagneticField.hh>
#include <G4ThreeVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ElectroMagneticField : G4ElectroMagneticField {
public:
   using G4ElectroMagneticField::G4ElectroMagneticField;

   void GetFieldValue(const G4double Point[4], G4double *Bfield) const override
   {
      py::gil_scoped_acquire gil;
      py::function           pyGetFieldValue =
         py::get_override(static_cast<const G4ElectroMagneticField *>(this), "GetFieldValue");

      if (pyGetFieldValue) {
         py::list pyBfield(6);
         py::list pointList(4);
         for (size_t i = 0; i < pyBfield.size(); i++) {
            pyBfield[i] = 0;
         }
         pointList[0]          = Point[0];
         pointList[1]          = Point[1];
         pointList[2]          = Point[2];
         pointList[3]          = Point[3];
         py::object pyretField = pyGetFieldValue(pointList, pyBfield);
         if (py::isinstance<py::list>(pyretField) && ((py::list)pyretField).size() == 6) {
            Bfield[0] = ((py::list)pyretField)[0].cast<G4double>();
            Bfield[1] = ((py::list)pyretField)[1].cast<G4double>();
            Bfield[2] = ((py::list)pyretField)[2].cast<G4double>();
            Bfield[3] = ((py::list)pyretField)[3].cast<G4double>();
            Bfield[4] = ((py::list)pyretField)[4].cast<G4double>();
            Bfield[5] = ((py::list)pyretField)[5].cast<G4double>();
         } else if (pyBfield.size() == 6) {
            Bfield[0] = pyBfield[0].cast<G4double>();
            Bfield[1] = pyBfield[1].cast<G4double>();
            Bfield[2] = pyBfield[2].cast<G4double>();
            Bfield[3] = pyBfield[3].cast<G4double>();
            Bfield[4] = pyBfield[4].cast<G4double>();
            Bfield[5] = pyBfield[5].cast<G4double>();
         } else {
            py::pybind11_fail("\"G4ElectroMagneticField::GetFieldValue\" Bfield must have 6 components");
         }
      } else {
         py::pybind11_fail("Tried to call pure virtual function \"G4ElectroMagneticField::GetFieldValue\"");
      }
   }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4ElectroMagneticField, DoesFieldChangeEnergy, );
   }
};

void export_G4ElectroMagneticField(py::module &m)
{
   py::class_<G4ElectroMagneticField, G4Field, PyG4ElectroMagneticField>(m, "G4ElectroMagneticField")
      .def(py::init<>())

      .def("DoesFieldChangeEnergy", &G4ElectroMagneticField::DoesFieldChangeEnergy)
      .def("GetFieldValue", &G4ElectroMagneticField::GetFieldValue);
}
