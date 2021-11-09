#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HarmonicPolMagField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HarmonicPolMagField : public G4HarmonicPolMagField, public py::trampoline_self_life_support {
public:
   using G4HarmonicPolMagField::G4HarmonicPolMagField;

   void GetFieldValue(const G4double Point[4], G4double *Bfield) const override
   {
      py::gil_scoped_acquire gil;
      py::function           pyGetFieldValue =
         py::get_override(static_cast<const G4HarmonicPolMagField *>(this), "GetFieldValue");

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
            py::pybind11_fail("\"G4HarmonicPolMagField::GetFieldValue\" Bfield must have 6 components");
         }
      } else {
         return G4HarmonicPolMagField::GetFieldValue(Point, Bfield);
      }
   }

   G4HarmonicPolMagField *Clone() const override
   {
      PYBIND11_OVERRIDE(G4HarmonicPolMagField *, G4HarmonicPolMagField, Clone, );
   }

   G4bool DoesFieldChangeEnergy() const override
   {
      PYBIND11_OVERRIDE(G4bool, G4HarmonicPolMagField, DoesFieldChangeEnergy, );
   }
};

void export_G4HarmonicPolMagField(py::module &m)
{
   py::class_<G4HarmonicPolMagField, PyG4HarmonicPolMagField, G4MagneticField>(m, "G4HarmonicPolMagField")

      .def(py::init<>())
      .def("__copy__", [](const G4HarmonicPolMagField &self) { return G4HarmonicPolMagField(self); })
      .def("__deepcopy__", [](const G4HarmonicPolMagField &self, py::dict) { return G4HarmonicPolMagField(self); })
      .def(
         "GetFieldValue",
         [](G4HarmonicPolMagField &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4HarmonicPolMagField::GetFieldValue\" yTrack must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4HarmonicPolMagField::GetFieldValue\" B must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"))

      .def("Clone", &G4HarmonicPolMagField::Clone, py::return_value_policy::reference);
}
