#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VWeightWindowAlgorithm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VWeightWindowAlgorithm : public G4VWeightWindowAlgorithm, public py::trampoline_self_life_support {
public:
   using G4VWeightWindowAlgorithm::G4VWeightWindowAlgorithm;

   G4Nsplit_Weight Calculate(G4double init_w, G4double lowerWeightBound) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Nsplit_Weight, G4VWeightWindowAlgorithm, Calculate, init_w, lowerWeightBound);
   }
};

void export_G4VWeightWindowAlgorithm(py::module &m)
{
   py::class_<G4VWeightWindowAlgorithm, PyG4VWeightWindowAlgorithm>(m, "G4VWeightWindowAlgorithm")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VWeightWindowAlgorithm &self) { return PyG4VWeightWindowAlgorithm(self); })
      .def("__deepcopy__",
           [](const PyG4VWeightWindowAlgorithm &self, py::dict) { return PyG4VWeightWindowAlgorithm(self); })

      .def("Calculate", &G4VWeightWindowAlgorithm::Calculate, py::arg("init_w"), py::arg("lowerWeightBound"));
}
