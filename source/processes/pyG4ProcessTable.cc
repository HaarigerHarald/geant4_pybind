#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ProcessTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ProcessTable(py::module &m)
{
   py::class_<G4ProcessTable, py::nodelete>(m, "G4ProcessTable", "process table")

      .def_static("GetProcessTable", &G4ProcessTable::GetProcessTable, py::return_value_policy::reference)
      .def("Length", &G4ProcessTable::Length)
      //.def("Insert",             &G4ProcessTable::Insert)  // protected
      //.def("Remove",             &G4ProcessTable::Remove)  // protected

      .def("FindProcess",
           py::overload_cast<const G4String &, const G4String &>(&G4ProcessTable::FindProcess, py::const_),
           py::return_value_policy::reference)

      .def("FindProcess",
           py::overload_cast<const G4String &, const G4ParticleDefinition *>(&G4ProcessTable::FindProcess, py::const_),
           py::return_value_policy::reference)

      .def("FindProcess",
           py::overload_cast<G4int, const G4ParticleDefinition *>(&G4ProcessTable::FindProcess, py::const_),
           py::return_value_policy::reference)

      .def("FindProcess",
           py::overload_cast<G4ProcessType, const G4ParticleDefinition *>(&G4ProcessTable::FindProcess, py::const_),
           py::return_value_policy::reference)

      .def("FindProcess",
           py::overload_cast<const G4String &, const G4ProcessManager *>(&G4ProcessTable::FindProcess, py::const_),
           py::return_value_policy::reference)

      .def("FindProcesses",
           [](G4ProcessTable &self) {
              py::list         procList;
              G4ProcessVector *procVec = self.FindProcesses();
              G4int            nproc   = procVec->size();
              for (G4int i = 0; i < nproc; i++) {
                 procList.append((*procVec)[i]);
              }
              return procList;
           })

      .def("FindProcesses",
           [](G4ProcessTable &self, const G4ProcessManager *procManager) {
              py::list         procList;
              G4ProcessVector *procVec = self.FindProcesses(procManager);
              G4int            nproc   = procVec->size();
              for (G4int i = 0; i < nproc; i++) {
                 procList.append((*procVec)[i]);
              }
              return procList;
           })

      .def("FindProcesses",
           [](G4ProcessTable &self, const G4String &pname) {
              py::list         procList;
              G4ProcessVector *procVec = self.FindProcesses(pname);
              G4int            nproc   = procVec->size();
              for (G4int i = 0; i < nproc; i++) {
                 procList.append((*procVec)[i]);
              }
              return procList;
           })

      .def("FindProcesses",
           [](G4ProcessTable &self, G4ProcessType ptype) {
              py::list         procList;
              G4ProcessVector *procVec = self.FindProcesses(ptype);
              G4int            nproc   = procVec->size();
              for (G4int i = 0; i < nproc; i++) {
                 procList.append((*procVec)[i]);
              }
              return procList;
           })

      .def("SetProcessActivation", py::overload_cast<const G4String &, G4bool>(&G4ProcessTable::SetProcessActivation))
      .def("SetProcessActivation",
           py::overload_cast<const G4String &, const G4String &, G4bool>(&G4ProcessTable::SetProcessActivation))

      .def("SetProcessActivation", py::overload_cast<const G4String &, const G4ParticleDefinition *, G4bool>(
                                      &G4ProcessTable::SetProcessActivation))

      .def("SetProcessActivation",
           py::overload_cast<const G4String &, G4ProcessManager *, G4bool>(&G4ProcessTable::SetProcessActivation))

      .def("SetProcessActivation", py::overload_cast<G4ProcessType, G4bool>(&G4ProcessTable::SetProcessActivation))
      .def("SetProcessActivation",
           py::overload_cast<G4ProcessType, const G4String &, G4bool>(&G4ProcessTable::SetProcessActivation))

      .def("SetProcessActivation", py::overload_cast<G4ProcessType, const G4ParticleDefinition *, G4bool>(
                                      &G4ProcessTable::SetProcessActivation))

      .def("SetProcessActivation",
           py::overload_cast<G4ProcessType, G4ProcessManager *, G4bool>(&G4ProcessTable::SetProcessActivation))

      .def("GetNameList", &G4ProcessTable::GetNameList, py::return_value_policy::reference)
      .def("DumpInfo", &G4ProcessTable::DumpInfo, py::arg("process"),
           py::arg("particle") = static_cast<const G4ParticleDefinition *>(nullptr))

      .def("SetVerboseLevel", &G4ProcessTable::SetVerboseLevel)
      .def("GetVerboseLevel", &G4ProcessTable::GetVerboseLevel);
}
