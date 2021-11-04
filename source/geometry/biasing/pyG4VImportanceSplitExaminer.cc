#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VImportanceSplitExaminer.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VImportanceSplitExaminer : public G4VImportanceSplitExaminer, public py::trampoline_self_life_support {
public:
   using G4VImportanceSplitExaminer::G4VImportanceSplitExaminer;

   G4Nsplit_Weight Examine(G4double w) const override
   {
      PYBIND11_OVERRIDE_PURE(G4Nsplit_Weight, G4VImportanceSplitExaminer, Examine, w);
   }
};

void export_G4VImportanceSplitExaminer(py::module &m)
{
   py::class_<G4VImportanceSplitExaminer, PyG4VImportanceSplitExaminer>(m, "G4VImportanceSplitExaminer")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VImportanceSplitExaminer &self) { return PyG4VImportanceSplitExaminer(self); })
      .def("__deepcopy__",
           [](const PyG4VImportanceSplitExaminer &self, py::dict) { return PyG4VImportanceSplitExaminer(self); })

      .def("Examine", &G4VImportanceSplitExaminer::Examine, py::arg("w"));
}
