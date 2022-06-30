#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DensityEffectCalculator.hh>
#include <G4Material.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DensityEffectCalculator(py::module &m)
{
   py::class_<G4DensityEffectCalculator>(m, "G4DensityEffectCalculator")

      .def("__copy__", [](const G4DensityEffectCalculator &self) { return new G4DensityEffectCalculator(self); })
      .def("__deepcopy__",
           [](const G4DensityEffectCalculator &self, py::dict) { return new G4DensityEffectCalculator(self); })

      .def(py::init<const G4Material *, G4int>())
      .def("ComputeDensityCorrection", &G4DensityEffectCalculator::ComputeDensityCorrection, py::arg("x"));
}
