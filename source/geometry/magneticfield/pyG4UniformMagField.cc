#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UniformMagField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UniformMagField : public G4UniformMagField, public py::trampoline_self_life_support {
public:
   using G4UniformMagField::G4UniformMagField;

   G4Field *Clone() const override { PYBIND11_OVERRIDE(G4Field *, G4UniformMagField, Clone, ); }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4UniformMagField, DoesFieldChangeEnergy, );
   }
};

void export_G4UniformMagField(py::module &m)
{
   py::class_<G4UniformMagField, PyG4UniformMagField, G4MagneticField>(m, "G4UniformMagField")

      .def(py::init<const G4ThreeVector &>(), py::arg("FieldVector"))
      .def(py::init<G4double, G4double, G4double>(), py::arg("vField"), py::arg("vTheta"), py::arg("vPhi"))
      .def("__copy__", [](const PyG4UniformMagField &self) { return PyG4UniformMagField(self); })
      .def("__deepcopy__", [](const PyG4UniformMagField &self, py::dict) { return PyG4UniformMagField(self); })
      .def(
         "GetFieldValue",
         [](G4UniformMagField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4UniformMagField::GetFieldValue\" yTrack must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4UniformMagField::GetFieldValue\" MagField must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"))

      .def("SetFieldValue", &G4UniformMagField::SetFieldValue, py::arg("newFieldValue"))
      .def("GetConstantFieldValue", &G4UniformMagField::GetConstantFieldValue)
      .def("Clone", &G4UniformMagField::Clone, py::return_value_policy::reference);
}
