#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VProcess.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VProcess(py::module &m)
{
   py::class_<G4VProcess>(m, "G4VProcess", "base class for process")

      .def("SetPILfactor", &G4VProcess::SetPILfactor)
      .def("GetPILfactor", &G4VProcess::GetPILfactor)
      .def("IsApplicable", &G4VProcess::IsApplicable)
      .def("BuildPhysicsTable", &G4VProcess::BuildPhysicsTable)
      .def("PreparePhysicsTable", &G4VProcess::PreparePhysicsTable)
      .def("StorePhysicsTable", &G4VProcess::StorePhysicsTable)
      .def("RetrievePhysicsTable", &G4VProcess::RetrievePhysicsTable)
      .def("GetPhysicsTableFileName", &G4VProcess::GetPhysicsTableFileName, py::arg("particle"), py::arg("directory"),
           py::arg("tableName"), py::arg("ascii") = false)

      .def("GetProcessName", &G4VProcess::GetProcessName)
      .def("GetProcessType", &G4VProcess::GetProcessType)
      .def("DumpInfo", &G4VProcess::DumpInfo)
      .def("SetVerboseLevel", &G4VProcess::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VProcess::GetVerboseLevel);
}
