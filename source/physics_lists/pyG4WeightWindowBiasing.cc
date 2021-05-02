#include <pybind11/pybind11.h>

#include <G4WeightWindowBiasing.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4WeightWindowBiasing) : public G4WeightWindowBiasing {
public:
   using G4WeightWindowBiasing::G4WeightWindowBiasing;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4WeightWindowBiasing, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4WeightWindowBiasing, ConstructProcess, ); }

   TRAMPOLINE_DESTRUCTOR(G4WeightWindowBiasing);
};

void export_G4WeightWindowBiasing(py::module &m)
{

   py::class_<G4WeightWindowBiasing, TRAMPOLINE_NAME(G4WeightWindowBiasing), G4VPhysicsConstructor,
              owntrans_ptr<G4WeightWindowBiasing>>(m, "G4WeightWindowBiasing")

      .def(py::init<const G4String &>(), py::arg("name") = "NoParallelWP")
      .def(py::init<G4GeometrySampler *, G4VWeightWindowAlgorithm *, G4PlaceOfAction, const G4String &>(),
           py::arg("msg"), py::arg("wwAlg"), py::arg("placeOfAction"), py::arg("name") = "NoParallelWP")

      .def("ConstructParticle", &G4WeightWindowBiasing::ConstructParticle)
      .def("ConstructProcess", &G4WeightWindowBiasing::ConstructProcess);
}
