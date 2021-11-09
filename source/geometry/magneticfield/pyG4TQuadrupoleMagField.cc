#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TQuadrupoleMagField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TQuadrupoleMagField : public G4TQuadrupoleMagField, public py::trampoline_self_life_support {
public:
   using G4TQuadrupoleMagField::G4TQuadrupoleMagField;

   void GetFieldValue(const G4double pos[4], G4double *field) const override
   {
      py::gil_scoped_acquire gil;
      py::function           pyGetFieldValue =
         py::get_override(static_cast<const G4TQuadrupoleMagField *>(this), "GetFieldValue");

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
            py::pybind11_fail("\"G4TQuadrupoleMagField::GetFieldValue\" field must have 6 components");
         }
      } else {
         return G4TQuadrupoleMagField::GetFieldValue(pos, field);
      }
   }

   G4TQuadrupoleMagField *Clone() const override
   {
      PYBIND11_OVERRIDE(G4TQuadrupoleMagField *, G4TQuadrupoleMagField, Clone, );
   }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TQuadrupoleMagField, DoesFieldChangeEnergy, );
   }
};

void export_G4TQuadrupoleMagField(py::module &m)
{
   py::class_<G4TQuadrupoleMagField, PyG4TQuadrupoleMagField, G4MagneticField>(m, "G4TQuadrupoleMagField")

      .def(py::init<G4double>(), py::arg("pGradient"))
      .def(py::init<G4double, G4ThreeVector, G4RotationMatrix *>(), py::arg("pGradient"), py::arg("pOrigin"),
           py::arg("pMatrix"))

      .def("__copy__", [](const G4TQuadrupoleMagField &self) { return G4TQuadrupoleMagField(self); })
      .def("__deepcopy__", [](const G4TQuadrupoleMagField &self, py::dict) { return G4TQuadrupoleMagField(self); })
      .def(
         "GetFieldValue",
         [](G4TQuadrupoleMagField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4TQuadrupoleMagField::GetFieldValue\" y must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4TQuadrupoleMagField::GetFieldValue\" B must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"))

      .def("Clone", &G4TQuadrupoleMagField::Clone, py::return_value_policy::reference);
}
