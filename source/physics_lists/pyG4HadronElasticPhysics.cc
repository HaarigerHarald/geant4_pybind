#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChargeExchangePhysics.hh>
#include <G4HadronDElasticPhysics.hh>
#include <G4HadronElasticPhysics.hh>
#include <G4HadronElasticPhysicsHP.hh>
#include <G4HadronElasticPhysicsLEND.hh>
#include <G4HadronElasticPhysicsPHP.hh>
#include <G4HadronElasticPhysicsXS.hh>
#include <G4HadronHElasticPhysics.hh>
#include <G4IonElasticPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_HADRON_ELASTIC_PHYSICS(name)                  \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4HadronElasticPhysics(py::module &m)
{
   ADD_HADRON_ELASTIC_PHYSICS(G4ChargeExchangePhysics);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronDElasticPhysics);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronElasticPhysics);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronElasticPhysicsHP);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronElasticPhysicsLEND);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronElasticPhysicsPHP);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronElasticPhysicsXS);
   ADD_HADRON_ELASTIC_PHYSICS(G4HadronHElasticPhysics);
   ADD_HADRON_ELASTIC_PHYSICS(G4IonElasticPhysics);
}
