#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4ParticleTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ParticleList {
public:
   typedef std::vector<G4ParticleDefinition *> ParticleList;
   typedef ParticleList::iterator              p_iterator;

   static ParticleList particleTableCache;

   p_iterator p_begin()
   {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      if (particleTableCache.size() != static_cast<size_t>(particleTable->size())) {
         particleTableCache.clear();
         G4ParticleTable::G4PTblDicIterator *theParticleIterator = particleTable->GetIterator();
         theParticleIterator->reset();
         while ((*theParticleIterator)()) {
            G4ParticleDefinition *particle = theParticleIterator->value();
            particleTableCache.push_back(particle);
         }
      }
      return particleTableCache.begin();
   }

   p_iterator p_end()
   {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      if (particleTableCache.size() != static_cast<size_t>(particleTable->size())) {
         particleTableCache.clear();
         G4ParticleTable::G4PTblDicIterator *theParticleIterator = particleTable->GetIterator();
         theParticleIterator->reset();
         while ((*theParticleIterator)()) {
            G4ParticleDefinition *particle = theParticleIterator->value();
            particleTableCache.push_back(particle);
         }
      }
      return particleTableCache.end();
   }
};

PyG4ParticleList::ParticleList PyG4ParticleList::particleTableCache;

// TODO

void export_PyG4ParticleList(py::module &m)
{
   py::class_<PyG4ParticleList>(m, "PyG4ParticleList", "particle list")
      .def(py::init<>())
      .def(
         "__iter__", [](PyG4ParticleList &self) { py::make_iterator(self.p_begin(), self.p_end()); }, py::is_operator())

      .def(
         "__getitem__",
         [](PyG4ParticleList &self, size_t i) {
            self.p_begin();
            return self.particleTableCache[i];
         },
         py::is_operator())

      .def_property_readonly("particles", [](PyG4ParticleList &self) {
         py::list list;
         for (auto it = self.p_begin(); it < self.p_end(); it++) {
            list.append(it);
         }
         return list;
      });
}
