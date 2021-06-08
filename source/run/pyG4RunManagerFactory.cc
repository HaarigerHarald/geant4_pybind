#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RunManagerFactory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RunManagerFactory(py::module &m)
{
   py::enum_<G4RunManagerType>(m, "G4RunManagerType")
      .value("Serial", G4RunManagerType::Serial)
      .value("SerialOnly", G4RunManagerType::SerialOnly)
      .value("MT", G4RunManagerType::MT)
      .value("MTOnly", G4RunManagerType::MTOnly)
      .value("Tasking", G4RunManagerType::Tasking)
      .value("TaskingOnly", G4RunManagerType::TaskingOnly)
      .value("TBB", G4RunManagerType::TBB)
      .value("TBBOnly", G4RunManagerType::TBBOnly)
      .value("Default", G4RunManagerType::Default);

   py::class_<G4RunManagerFactory>(m, "G4RunManagerFactory")
      .def_static("CreateRunManager",
                  static_cast<G4RunManager *(*)(G4RunManagerType, G4VUserTaskQueue *, G4bool, G4int)>(
                     &G4RunManagerFactory::CreateRunManager),
                  py::arg("_type")  = G4RunManagerType::Default,
                  py::arg("_queue") = static_cast<G4VUserTaskQueue *>(nullptr), py::arg("fail_if_unavail") = true,
                  py::arg("nthreads") = 0, py::return_value_policy::reference)

      .def_static("CreateRunManager",
                  static_cast<G4RunManager *(*)(G4RunManagerType, G4bool, G4int, G4VUserTaskQueue *)>(
                     &G4RunManagerFactory::CreateRunManager),
                  py::arg("_type") = G4RunManagerType::Default, py::arg("fail_if_unavail") = true,
                  py::arg("nthreads") = 0, py::arg("_queue") = static_cast<G4VUserTaskQueue *>(nullptr),
                  py::return_value_policy::reference)

      .def_static("CreateRunManager",
                  static_cast<G4RunManager *(*)(G4RunManagerType, G4int, G4bool, G4VUserTaskQueue *)>(
                     &G4RunManagerFactory::CreateRunManager),
                  py::arg("_type") = G4RunManagerType::Default, py::arg("nthreads") = 0,
                  py::arg("fail_if_unavail") = true, py::arg("_queue") = static_cast<G4VUserTaskQueue *>(nullptr),
                  py::return_value_policy::reference)

      .def_static("GetDefault", &G4RunManagerFactory::GetDefault)
      .def_static("GetName", &G4RunManagerFactory::GetName)
      .def_static("GetType", &G4RunManagerFactory::GetType)
      .def_static("GetOptions", &G4RunManagerFactory::GetOptions)
      .def_static("GetMasterRunManager", &G4RunManagerFactory::GetMasterRunManager, py::return_value_policy::reference);

   // TODO
   // .def_static("GetMTMasterRunManager", &G4RunManagerFactory::GetMTMasterRunManager,
   //             py::return_value_policy::reference)

   // .def_static("GetMasterRunManagerKernel", &G4RunManagerFactory::GetMasterRunManagerKernel,
   //             py::return_value_policy::reference);
}