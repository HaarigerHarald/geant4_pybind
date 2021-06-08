#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HadronInelasticQBBC.hh>
#include <G4HadronPhysicsFTF_BIC.hh>
#include <G4HadronPhysicsFTFP_BERT_ATL.hh>
#include <G4HadronPhysicsFTFP_BERT_HP.hh>
#include <G4HadronPhysicsFTFP_BERT_TRV.hh>
#include <G4HadronPhysicsFTFP_BERT.hh>
#include <G4HadronPhysicsFTFQGSP_BERT.hh>
#include <G4HadronPhysicsINCLXX.hh>
#include <G4HadronPhysicsNuBeam.hh>
#include <G4HadronPhysicsQGS_BIC.hh>
#include <G4HadronPhysicsQGSP_BERT_HP.hh>
#include <G4HadronPhysicsQGSP_BERT.hh>
#include <G4HadronPhysicsQGSP_BIC_AllHP.hh>
#include <G4HadronPhysicsQGSP_BIC_HP.hh>
#include <G4HadronPhysicsQGSP_BIC.hh>
#include <G4HadronPhysicsQGSP_FTFP_BERT.hh>
#include <G4HadronPhysicsShielding.hh>
#include <G4HadronPhysicsShieldingLEND.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_HADRON_INELASTIC_PHYSICS(name)                \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4HadronInelasticPhysics(py::module &m)
{
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronInelasticQBBC);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTF_BIC);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTFP_BERT_ATL);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTFP_BERT_HP);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTFP_BERT_TRV);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTFP_BERT);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsFTFQGSP_BERT);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsINCLXX);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsNuBeam);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGS_BIC);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_BERT_HP);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_BERT);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_BIC_AllHP);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_BIC_HP);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_BIC);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsQGSP_FTFP_BERT);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsShielding);
   ADD_HADRON_INELASTIC_PHYSICS(G4HadronPhysicsShieldingLEND);
}
