#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ImportanceAlgorithm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ImportanceAlgorithm : public G4ImportanceAlgorithm, public py::trampoline_self_life_support {
public:
   using G4ImportanceAlgorithm::G4ImportanceAlgorithm;

   G4Nsplit_Weight Calculate(G4double ipre, G4double ipost, G4double init_w) const override
   {
      PYBIND11_OVERRIDE(G4Nsplit_Weight, G4ImportanceAlgorithm, Calculate, ipre, ipost, init_w);
   }
};

void export_G4ImportanceAlgorithm(py::module &m)
{
   py::class_<G4ImportanceAlgorithm, PyG4ImportanceAlgorithm, G4VImportanceAlgorithm>(m, "G4ImportanceAlgorithm")

      .def(py::init<>())
      .def("__copy__", [](const PyG4ImportanceAlgorithm &self) { return PyG4ImportanceAlgorithm(self); })
      .def("__deepcopy__", [](const PyG4ImportanceAlgorithm &self, py::dict) { return PyG4ImportanceAlgorithm(self); })
      .def("Calculate", &G4ImportanceAlgorithm::Calculate, py::arg("ipre"), py::arg("ipost"), py::arg("init_w"));
}
