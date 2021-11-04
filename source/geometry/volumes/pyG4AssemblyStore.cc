#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4AssemblyStore.hh>
#include <G4AssemblyVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4AssemblyStore : public G4AssemblyStore {
public:
   using G4AssemblyStore::G4AssemblyStore;
   ~PublicG4AssemblyStore() {}
};

void export_G4AssemblyStore(py::module &m)
{
   py::bind_vector<PublicG4AssemblyStore, py::nodelete>(m, "G4AssemblyStore")

      .def("__copy__", [](const PublicG4AssemblyStore &self) { return PublicG4AssemblyStore(self); })
      .def("__deepcopy__", [](const PublicG4AssemblyStore &self, py::dict) { return PublicG4AssemblyStore(self); })
      .def_static("Register", &G4AssemblyStore::Register, py::arg("pAssembly"))
      .def_static("DeRegister", &G4AssemblyStore::DeRegister, py::arg("pAssembly"))
      .def_static("GetInstance", &G4AssemblyStore::GetInstance, py::return_value_policy::reference)
      .def_static("SetNotifier", &G4AssemblyStore::SetNotifier, py::arg("pNotifier"))
      .def_static("Clean", &G4AssemblyStore::Clean)
      .def("GetAssembly", &G4AssemblyStore::GetAssembly, py::arg("id"), py::arg("verbose") = true,
           py::return_value_policy::reference);
}
