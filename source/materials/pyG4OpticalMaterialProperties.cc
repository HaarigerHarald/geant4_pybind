#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

namespace G4OpticalMaterialProperties {

void                      ConvertToEnergy(std::vector<G4double> &wavelength);
G4MaterialPropertyVector *GetRefractiveIndex(const G4String &material);
G4MaterialPropertyVector *GetProperty(const G4String &key, const G4String &mat);

} // namespace G4OpticalMaterialProperties

void export_G4OpticalMaterialProperties(py::module &m)
{
   struct ScopedG4OpticalMaterialProperties {};

   py::class_<ScopedG4OpticalMaterialProperties>(m, "G4OpticalMaterialProperties")

      .def_static("ConvertToEnergy", &G4OpticalMaterialProperties::ConvertToEnergy, py::arg("wavelength"))
      .def_static("GetProperty", &G4OpticalMaterialProperties::GetProperty, py::arg("key"), py::arg("mat"),
                  py::return_value_policy::reference)

      .def_static("GetRefractiveIndex", &G4OpticalMaterialProperties::GetRefractiveIndex, py::arg("material"),
                  py::return_value_policy::reference);
}
