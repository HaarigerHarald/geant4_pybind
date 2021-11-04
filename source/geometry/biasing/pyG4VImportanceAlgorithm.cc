#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VImportanceAlgorithm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VImportanceAlgorithm : public G4VImportanceAlgorithm, public py::trampoline_self_life_support {
public:
   using G4VImportanceAlgorithm::G4VImportanceAlgorithm;

   G4Nsplit_Weight Calculate(G4double ipre, G4double ipost, G4double init_w) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Nsplit_Weight, G4VImportanceAlgorithm, Calculate, ipre, ipost, init_w);
   }
};

void export_G4VImportanceAlgorithm(py::module &m)
{
   py::class_<G4VImportanceAlgorithm, PyG4VImportanceAlgorithm>(m, "G4VImportanceAlgorithm")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VImportanceAlgorithm &self) { return PyG4VImportanceAlgorithm(self); })
      .def("__deepcopy__",
           [](const PyG4VImportanceAlgorithm &self, py::dict) { return PyG4VImportanceAlgorithm(self); })

      .def("Calculate", &G4VImportanceAlgorithm::Calculate, py::arg("ipre"), py::arg("ipost"), py::arg("init_w"));
}
