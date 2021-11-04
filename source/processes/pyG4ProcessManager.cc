#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ProcessManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ProcessManager(py::module &m)
{
   py::enum_<G4ProcessVectorTypeIndex>(m, "G4ProcessVectorTypeIndex")
      .value("typeGPIL", typeGPIL)
      .value("typeDoIt", typeDoIt)
      .export_values();

   py::enum_<G4ProcessVectorDoItIndex>(m, "G4ProcessVectorDoItIndex")
      .value("idxAll", idxAll)
      .value("idxAtRest", idxAtRest)
      .value("idxAlongStep", idxAlongStep)
      .value("idxPostStep", idxPostStep)
      .export_values();

   py::enum_<G4ProcessVectorOrdering>(m, "G4ProcessVectorOrdering")
      .value("ordInActive", ordInActive)
      .value("ordDefault", ordDefault)
      .value("ordLast", ordLast)
      .export_values();

   py::class_<G4ProcessManager>(m, "G4ProcessManager", "process manager class")
      .def(py::init<const G4ParticleDefinition *>())

      .def("GetProcessList",
           [](const G4ProcessManager &self) {
              py::list         procList;
              G4ProcessVector *procVec = self.GetProcessList();
              size_t           nproc   = procVec->size();
              for (size_t i = 0; i < nproc; i++) {
                 procList.append((*procVec)[i]);
              }
              return procList;
           })

      .def("GetProcessListLength", &G4ProcessManager::GetProcessListLength)
      .def("GetProcessIndex", &G4ProcessManager::GetProcessIndex)
      .def(
         "GetProcessVector",
         [](const G4ProcessManager &self, G4ProcessVectorDoItIndex idx, G4ProcessVectorTypeIndex typ = typeGPIL) {
            py::list         procList;
            G4ProcessVector *procVec = self.GetProcessVector(idx, typ);
            size_t           nproc   = procVec->size();
            for (size_t i = 0; i < nproc; i++) {
               procList.append((*procVec)[i]);
            }
            return procList;
         },
         py::arg("idx"), py::arg("typ") = typeGPIL)

      .def(
         "GetAtRestProcessVector",
         [](const G4ProcessManager &self, G4ProcessVectorTypeIndex typ = typeGPIL) {
            py::list         procList;
            G4ProcessVector *procVec = self.GetAtRestProcessVector(typ);
            size_t           nproc   = procVec->size();
            for (size_t i = 0; i < nproc; i++) {
               procList.append((*procVec)[i]);
            }
            return procList;
         },
         py::arg("typ") = typeGPIL)

      .def(
         "GetAlongStepProcessVector",
         [](const G4ProcessManager &self, G4ProcessVectorTypeIndex typ = typeGPIL) {
            py::list         procList;
            G4ProcessVector *procVec = self.GetAlongStepProcessVector(typ);
            size_t           nproc   = procVec->size();
            for (size_t i = 0; i < nproc; i++) {
               procList.append((*procVec)[i]);
            }
            return procList;
         },
         py::arg("typ") = typeGPIL)

      .def(
         "GetPostStepProcessVector",
         [](const G4ProcessManager &self, G4ProcessVectorTypeIndex typ = typeGPIL) {
            py::list         procList;
            G4ProcessVector *procVec = self.GetPostStepProcessVector(typ);
            size_t           nproc   = procVec->size();
            for (size_t i = 0; i < nproc; i++) {
               procList.append((*procVec)[i]);
            }
            return procList;
         },
         py::arg("typ") = typeGPIL)

      .def("GetProcessVectorIndex", &G4ProcessManager::GetProcessVectorIndex, py::arg("process"), py::arg("idx"),
           py::arg("typ") = typeGPIL)

      .def("GetAtRestIndex", &G4ProcessManager::GetAtRestIndex, py::arg("process"), py::arg("typ") = typeGPIL)
      .def("GetAlongStepIndex", &G4ProcessManager::GetAlongStepIndex, py::arg("process"), py::arg("typ") = typeGPIL)
      .def("GetPostStepIndex", &G4ProcessManager::GetPostStepIndex, py::arg("process"), py::arg("typ") = typeGPIL)

      .def("AddProcess", &G4ProcessManager::AddProcess, py::arg("process"), py::arg("ordAtRestDoIt") = -1,
           py::arg("ordAlongStepDoIt") = -1, py::arg("ordPostStepDoIt") = -1)

      .def("AddRestProcess", &G4ProcessManager::AddRestProcess, py::arg("process"), py::arg("ord") = ordDefault)
      .def("AddDiscreteProcess", &G4ProcessManager::AddDiscreteProcess, py::arg("process"), py::arg("ord") = ordDefault)
      .def("AddContinuousProcess", &G4ProcessManager::AddContinuousProcess, py::arg("process"),
           py::arg("ord") = ordDefault)

      .def("GetProcessOrdering", &G4ProcessManager::GetProcessOrdering)
      .def("SetProcessOrdering", &G4ProcessManager::SetProcessOrdering, py::arg("process"), py::arg("idDoIt"),
           py::arg("ordDoIt") = ordDefault)

      .def("SetProcessOrderingToFirst", &G4ProcessManager::SetProcessOrderingToFirst)
      .def("SetProcessOrderingToLast", &G4ProcessManager::SetProcessOrderingToLast)

      .def("RemoveProcess", py::overload_cast<G4VProcess *>(&G4ProcessManager::RemoveProcess),
           py::return_value_policy::reference)

      .def("RemoveProcess", py::overload_cast<G4int>(&G4ProcessManager::RemoveProcess),
           py::return_value_policy::reference)

      .def("SetProcessActivation", py::overload_cast<G4VProcess *, G4bool>(&G4ProcessManager::SetProcessActivation),
           py::return_value_policy::reference)

      .def("SetProcessActivation", py::overload_cast<G4int, G4bool>(&G4ProcessManager::SetProcessActivation),
           py::return_value_policy::reference)

      .def("GetProcessActivation", py::overload_cast<G4VProcess *>(&G4ProcessManager::GetProcessActivation, py::const_))
      .def("GetProcessActivation", py::overload_cast<G4int>(&G4ProcessManager::GetProcessActivation, py::const_))

      .def("GetParticleType", &G4ProcessManager::GetParticleType, py::return_value_policy::reference_internal)
      .def("SetParticleType", &G4ProcessManager::SetParticleType)
      .def("DumpInfo", &G4ProcessManager::DumpInfo)
      .def("SetVerboseLevel", &G4ProcessManager::SetVerboseLevel)
      .def("GetVerboseLevel", &G4ProcessManager::GetVerboseLevel);
}
