#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VVolumeMaterialScanner.hh>
#include <G4Material.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VVolumeMaterialScanner : public G4VVolumeMaterialScanner, public py::trampoline_self_life_support {
public:
   using G4VVolumeMaterialScanner::G4VVolumeMaterialScanner;

   G4int GetNumberOfMaterials() const override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VVolumeMaterialScanner, GetNumberOfMaterials, );
   }

   G4Material *GetMaterial(G4int idx) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Material *, G4VVolumeMaterialScanner, GetMaterial, idx);
   }
};

void export_G4VVolumeMaterialScanner(py::module &m)
{
   py::class_<G4VVolumeMaterialScanner, PyG4VVolumeMaterialScanner>(m, "G4VVolumeMaterialScanner")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VVolumeMaterialScanner &self) { return PyG4VVolumeMaterialScanner(self); })
      .def("__deepcopy__",
           [](const PyG4VVolumeMaterialScanner &self, py::dict) { return PyG4VVolumeMaterialScanner(self); })

      .def("GetNumberOfMaterials", &G4VVolumeMaterialScanner::GetNumberOfMaterials)
      .def("GetMaterial", &G4VVolumeMaterialScanner::GetMaterial, py::arg("idx"), py::return_value_policy::reference);
}
