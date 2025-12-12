#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4WeightWindowStore.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4WeightWindowStore(py::module &m)
{
   py::class_<G4WeightWindowStore, G4VWeightWindowStore, py::nodelete>(m, "G4WeightWindowStore")

      .def_static("GetInstance", py::overload_cast<>(&G4WeightWindowStore::GetInstance),
                  py::return_value_policy::reference)

      .def_static("GetInstance", py::overload_cast<G4String const &>(&G4WeightWindowStore::GetInstance),
                  py::arg("ParallelWorldName"), py::return_value_policy::reference)

      .def("GetLowerWeight", &G4WeightWindowStore::GetLowerWeight, py::arg("gCell"), py::arg("partEnergy"))
      .def("IsKnown", &G4WeightWindowStore::IsKnown, py::arg("gCell"))
      .def("Clear", &G4WeightWindowStore::Clear)
      .def("SetWorldVolume", &G4WeightWindowStore::SetWorldVolume)
      .def("SetParallelWorldVolume", &G4WeightWindowStore::SetParallelWorldVolume, py::arg("paraName"))
      .def("GetWorldVolume", &G4WeightWindowStore::GetWorldVolume)
      .def("GetParallelWorldVolumePointer", &G4WeightWindowStore::GetParallelWorldVolumePointer,
           py::return_value_policy::reference)

      .def("AddLowerWeights", &G4WeightWindowStore::AddLowerWeights, py::arg("gCell"), py::arg("lowerWeights"))
      .def("AddUpperEboundLowerWeightPairs", &G4WeightWindowStore::AddUpperEboundLowerWeightPairs, py::arg("gCell"),
           py::arg("enWeMap"))

      .def("SetGeneralUpperEnergyBounds", &G4WeightWindowStore::SetGeneralUpperEnergyBounds, py::arg("enBounds"));
}
