#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagneticField : public G4MagneticField, public py::trampoline_self_life_support {
public:
   using G4MagneticField::G4MagneticField;

   void GetFieldValue(const G4double Point[4], G4double *Bfield) const override
   {
      py::gil_scoped_acquire gil;
      py::function pyGetFieldValue = py::get_override(static_cast<const G4MagneticField *>(this), "GetFieldValue");

      if (pyGetFieldValue) {
         py::list pyBfield(6);
         py::list pointList(4);
         for (size_t i = 0; i < pyBfield.size(); i++) {
            pyBfield[i] = Bfield[i];
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
         } else if (pyBfield.size() >= 3) {
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

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4MagneticField, DoesFieldChangeEnergy, );
   }

   G4Field *Clone() const override { PYBIND11_OVERRIDE(G4Field *, G4MagneticField, Clone, ); }
};

void export_G4MagneticField(py::module &m)
{
   py::class_<G4MagneticField, PyG4MagneticField, G4Field>(m, "G4MagneticField")

      .def(py::init<>())
      .def("__copy__", [](const PyG4MagneticField &self) { return PyG4MagneticField(self); })
      .def("__deepcopy__", [](const PyG4MagneticField &self, py::dict) { return PyG4MagneticField(self); })
      .def("DoesFieldChangeEnergy", &G4MagneticField::DoesFieldChangeEnergy)
      .def(
         "GetFieldValue",
         [](G4MagneticField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"$1::GetFieldValue\" Point must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"$1::GetFieldValue\" Bfield must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"));
}
