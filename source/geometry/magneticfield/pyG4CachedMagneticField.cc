#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CachedMagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4CachedMagneticField : public G4CachedMagneticField, public py::trampoline_self_life_support {
public:
   using G4CachedMagneticField::G4CachedMagneticField;

   void GetFieldValue(const G4double pos[4], G4double *field) const override
   {
      py::gil_scoped_acquire gil;
      py::function           pyGetFieldValue =
         py::get_override(static_cast<const G4CachedMagneticField *>(this), "GetFieldValue");

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
            py::pybind11_fail("\"G4CachedMagneticField::GetFieldValue\" field must have 6 components");
         }
      } else {
         return G4CachedMagneticField::GetFieldValue(pos, field);
      }
   }

   G4Field *Clone() const override { PYBIND11_OVERRIDE(G4Field *, G4CachedMagneticField, Clone, ); }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4CachedMagneticField, DoesFieldChangeEnergy, );
   }
};

void export_G4CachedMagneticField(py::module &m)
{
   py::class_<G4CachedMagneticField, PyG4CachedMagneticField, G4MagneticField>(m, "G4CachedMagneticField")

      .def(py::init<G4MagneticField *, G4double>(), py::arg("arg0"), py::arg("distanceConst"))
      .def("__copy__", [](const PyG4CachedMagneticField &self) { return PyG4CachedMagneticField(self); })
      .def("__deepcopy__", [](const PyG4CachedMagneticField &self, py::dict) { return PyG4CachedMagneticField(self); })
      .def(
         "GetFieldValue",
         [](G4CachedMagneticField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4CachedMagneticField::GetFieldValue\" Point must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4CachedMagneticField::GetFieldValue\" Bfield must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"))

      .def("GetConstDistance", &G4CachedMagneticField::GetConstDistance)
      .def("SetConstDistance", &G4CachedMagneticField::SetConstDistance, py::arg("dist"))
      .def("GetCountCalls", &G4CachedMagneticField::GetCountCalls)
      .def("GetCountEvaluations", &G4CachedMagneticField::GetCountEvaluations)
      .def("ClearCounts", &G4CachedMagneticField::ClearCounts)
      .def("ReportStatistics", &G4CachedMagneticField::ReportStatistics)
      .def("Clone", &G4CachedMagneticField::Clone, py::return_value_policy::reference);
}
