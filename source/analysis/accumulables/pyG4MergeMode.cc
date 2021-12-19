#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MergeMode.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MergeMode(py::module &m)
{
   py::enum_<G4MergeMode>(m, "G4MergeMode")
      .value("kAddition", G4MergeMode::kAddition)
      .value("kMultiplication", G4MergeMode::kMultiplication)
      .value("kMaximum", G4MergeMode::kMaximum)
      .value("kMinimum", G4MergeMode::kMinimum);

   struct ScopedG4Accumulables {
   };

   py::class_<ScopedG4Accumulables>(m, "G4Accumulables")
      .def_static("GetMergeMode", &G4Accumulables::GetMergeMode, py::arg("mergeModeName"));
}
