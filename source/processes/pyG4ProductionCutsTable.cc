#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ProductionCutsTable.hh>
#include <G4Material.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ProductionCutsTable(py::module &m)
{
   py::class_<G4ProductionCutsTable, py::nodelete>(m, "G4ProductionCutsTable", "production cuts table")

      .def_static("GetProductionCutsTable", &G4ProductionCutsTable::GetProductionCutsTable,
                  py::return_value_policy::reference)

      // TODO

      .def("GetLowEdgeEnergy", &G4ProductionCutsTable::GetLowEdgeEnergy)
      .def("GetHighEdgeEnergy", &G4ProductionCutsTable::GetHighEdgeEnergy)
      .def("SetEnergyRange", &G4ProductionCutsTable::SetEnergyRange)
      .def("DumpCouples", &G4ProductionCutsTable::DumpCouples)
      .def("IsModified", &G4ProductionCutsTable::IsModified)
      .def("ConvertRangeToEnergy", &G4ProductionCutsTable::ConvertRangeToEnergy)
      .def("SetVerboseLevel", &G4ProductionCutsTable::SetVerboseLevel)
      .def("GetVerboseLevel", &G4ProductionCutsTable::GetVerboseLevel);
}
