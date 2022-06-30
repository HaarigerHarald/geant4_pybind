#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExtendedMaterial.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ExtendedMaterial : public G4ExtendedMaterial, public py::trampoline_self_life_support {
public:
   using G4ExtendedMaterial::G4ExtendedMaterial;

   G4bool IsExtended() const override { PYBIND11_OVERRIDE(G4bool, G4ExtendedMaterial, IsExtended, ); }
};

void export_G4ExtendedMaterial(py::module &m)
{
   py::class_<G4ExtendedMaterial, PyG4ExtendedMaterial, G4Material, py::nodelete>(m, "G4ExtendedMaterial")

      .def(py::init<const G4String &, const G4Material *>(), py::arg("name"), py::arg("baseMaterial"))
      .def(py::init<const G4String &, G4double, G4double, G4double, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("z"), py::arg("a"), py::arg("density"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def(py::init<const G4String &, G4double, G4int, G4State, G4double, G4double>(), py::arg("name"),
           py::arg("density"), py::arg("nComponents"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def(py::init<const G4String &, G4double, const G4ExtendedMaterial *, G4State, G4double, G4double>(),
           py::arg("name"), py::arg("density"), py::arg("baseMaterial"), py::arg("state") = kStateUndefined,
           py::arg("temp") = NTP_Temperature, py::arg_v("pressure", CLHEP::STP_Pressure, "STP_Pressure"))

      .def("GetNumberOfExtensions", &G4ExtendedMaterial::GetNumberOfExtensions)
      .def("IsExtended", &G4ExtendedMaterial::IsExtended)
      .def("Print", &G4ExtendedMaterial::Print, py::arg("flux"))
      .def("RegisterExtension", &G4ExtendedMaterial::RegisterExtension, py::arg("extension"))
      .def("RetrieveExtension", &G4ExtendedMaterial::RetrieveExtension, py::arg("name"),
           py::return_value_policy::reference)

      .def(
         "__iter__", [](G4ExtendedMaterial &self) { return py::make_iterator(self.begin(), self.end()); },
         py::keep_alive<0, 1>(), py::is_operator());
}
