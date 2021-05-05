#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AttDefStore.hh>
#include <G4AttDef.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class ScopeG4AttDefStore {
};

void export_G4AttDefStore(py::module &m)
{
   py::class_<ScopeG4AttDefStore, std::unique_ptr<ScopeG4AttDefStore, py::nodelete>>(m, "G4AttDefStore")
      .def_static("GetInstance",
                  [](const G4String &storeKey) {
                     G4bool                        isNew;
                     std::map<G4String, G4AttDef> *store = G4AttDefStore::GetInstance(storeKey, isNew);
                     return py::make_tuple(store, isNew);
                  })
      .def_static("GetStoreKey", [](const std::map<G4String, G4AttDef> *definitions) {
         G4String key;
         G4bool   contains = G4AttDefStore::GetStoreKey(definitions, key);
         return py::make_tuple(contains, key);
      });
}
