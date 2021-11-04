#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4WeightWindowAlgorithm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4WeightWindowAlgorithm : public G4WeightWindowAlgorithm, public py::trampoline_self_life_support {
public:
   using G4WeightWindowAlgorithm::G4WeightWindowAlgorithm;

   G4Nsplit_Weight Calculate(G4double init_w, G4double lowerWeightBound) const override
   {
      PYBIND11_OVERRIDE(G4Nsplit_Weight, G4WeightWindowAlgorithm, Calculate, init_w, lowerWeightBound);
   }
};

void export_G4WeightWindowAlgorithm(py::module &m)
{
   py::class_<G4WeightWindowAlgorithm, PyG4WeightWindowAlgorithm, G4VWeightWindowAlgorithm>(m,
                                                                                            "G4WeightWindowAlgorithm")

      .def(py::init<G4double, G4double, G4int>(), py::arg("upperLimitFactor") = 5, py::arg("survivalFactor") = 3,
           py::arg("maxNumberOfSplits") = 5)

      .def("__copy__", [](const PyG4WeightWindowAlgorithm &self) { return PyG4WeightWindowAlgorithm(self); })
      .def("__deepcopy__",
           [](const PyG4WeightWindowAlgorithm &self, py::dict) { return PyG4WeightWindowAlgorithm(self); })

      .def("Calculate", &G4WeightWindowAlgorithm::Calculate, py::arg("init_w"), py::arg("lowerWeightBound"));
}
