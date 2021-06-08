#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RunManagerKernel.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RunManagerKernel(py::module &m)
{
   py::class_<G4RunManagerKernel, py::nodelete>(m, "G4RunManagerKernel", "run manager kernel")

      .def(py::init<>())
      .def_static("GetRunManagerKernel", &G4RunManagerKernel::GetRunManagerKernel,
                  "Get an instance of G4RunManagerKernel", py::return_value_policy::reference)
      // TODO
      //.def("DefineWorldVolume", &G4RunManagerKernel::DefineWorldVolume)
      //.def("SetPhysics", &G4RunManagerKernel::SetPhysics)
      //.def("InitializePhysics", &G4RunManagerKernel::InitializePhysics)
      .def("RunInitialization", &G4RunManagerKernel::RunInitialization, py::arg("fakeRun") = false)
      //.def("RunTermination", &G4RunManagerKernel::RunTermination)
      //.def("UpdateRegion", &G4RunManagerKernel::UpdateRegion)
      //.def("DumpRegion", &G4RunManagerKernel::DumpRegion)
      //.def("DumpRegion", &G4RunManagerKernel::DumpRegion)
      //.def("GeometryHasBeenModified",
      //&G4RunManagerKernel::GeometryHasBeenModified)
      //.def("PhysicsHasBeenModified",
      //&G4RunManagerKernel::PhysicsHasBeenModified)
      //.def("GetEventManager", &G4RunManagerKernel::GetEventManager,
      //...)
      //.def("GetStackManager", &G4RunManagerKernel::GetStackManager,
      //...)
      //.def("GetTrackingManager", &G4RunManagerKernel::GetTrackingManager,
      //...)
      //.def("SetPrimaryTransformer", &G4RunManagerKernel::SetPrimaryTransformer)
      //.def("GetPrimaryTransformer", &G4RunManagerKernel::GetPrimaryTransformer,
      //...)
      //.def("GetVersionString", &G4RunManagerKernel::GetVersionString)
      //.def("SetVerboseLevel", &G4RunManagerKernel::SetVerboseLevel)
      //.def("SetGeometryToBeOptimized",
      //&G4RunManagerKernel::SetGeometryToBeOptimized)
      ;
}
