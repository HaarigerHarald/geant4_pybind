#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SolidStore.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SolidStore(py::module &m)
{
   py::class_<G4SolidStore, py::nodelete>(m, "G4SolidStore")

      .def_static("Register", &G4SolidStore::Register, py::arg("pSolid"))
      .def_static("DeRegister", &G4SolidStore::DeRegister, py::arg("pSolid"))
      .def_static("GetInstance", &G4SolidStore::GetInstance, py::return_value_policy::reference)
      .def_static("SetNotifier", &G4SolidStore::SetNotifier, py::arg("pNotifier"))
      .def_static("Clean", &G4SolidStore::Clean)
      .def("GetSolid", &G4SolidStore::GetSolid, py::arg("name"), py::arg("verbose") = true,
           py::return_value_policy::reference);
}
