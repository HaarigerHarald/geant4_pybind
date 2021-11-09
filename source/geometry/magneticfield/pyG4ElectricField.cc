#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ElectricField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ElectricField : public G4ElectricField, public py::trampoline_self_life_support {
public:
   using G4ElectricField::G4ElectricField;

   void GetFieldValue(const G4double pos[4], G4double *field) const override
   {
      py::gil_scoped_acquire gil;
      py::function pyGetFieldValue = py::get_override(static_cast<const G4ElectricField *>(this), "GetFieldValue");

      if (pyGetFieldValue) {
         py::list pyField(6);
         py::list pointList(4);
         for (size_t i = 0; i < pyField.size(); i++) {
            pyField[i] = field[i];
         }
         pointList[0]          = pos[0];
         pointList[1]          = pos[1];
         pointList[2]          = pos[2];
         pointList[3]          = pos[3];
         py::object pyretField = pyGetFieldValue(pointList, pyField);
         if (py::isinstance<py::list>(pyretField) && ((py::list)pyretField).size() == 6) {
            field[0] = ((py::list)pyretField)[0].cast<G4double>();
            field[1] = ((py::list)pyretField)[1].cast<G4double>();
            field[2] = ((py::list)pyretField)[2].cast<G4double>();
            field[3] = ((py::list)pyretField)[3].cast<G4double>();
            field[4] = ((py::list)pyretField)[4].cast<G4double>();
            field[5] = ((py::list)pyretField)[5].cast<G4double>();
         } else if (pyField.size() == 6) {
            field[0] = pyField[0].cast<G4double>();
            field[1] = pyField[1].cast<G4double>();
            field[2] = pyField[2].cast<G4double>();
            field[3] = pyField[3].cast<G4double>();
            field[4] = pyField[4].cast<G4double>();
            field[5] = pyField[5].cast<G4double>();
         } else {
            py::pybind11_fail("\"G4ElectricField::GetFieldValue\" field must have 6 components");
         }
      } else {
         py::pybind11_fail("Tried to call pure virtual function \"G4ElectricField::GetFieldValue\"");
      }
   }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ElectricField, DoesFieldChangeEnergy, );
   }

   G4Field *Clone() const override { PYBIND11_OVERRIDE(G4Field *, G4ElectricField, Clone, ); }
};

void export_G4ElectricField(py::module &m)
{
   py::class_<G4ElectricField, PyG4ElectricField, G4ElectroMagneticField>(m, "G4ElectricField")

      .def(py::init<>())
      .def("__copy__", [](const PyG4ElectricField &self) { return PyG4ElectricField(self); })
      .def("__deepcopy__", [](const PyG4ElectricField &self, py::dict) { return PyG4ElectricField(self); })
      .def("DoesFieldChangeEnergy", &G4ElectricField::DoesFieldChangeEnergy)
      .def(
         "GetFieldValue",
         [](G4ElectricField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4ElectricField::GetFieldValue\" Point must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4ElectricField::GetFieldValue\" field must have 6 components");
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
