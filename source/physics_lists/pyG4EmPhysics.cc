#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EmDNAChemistry_option1.hh>
#include <G4EmDNAChemistry_option2.hh>
#include <G4EmDNAChemistry_option3.hh>
#include <G4EmDNAChemistry.hh>
#include <G4EmDNAPhysics_option1.hh>
#include <G4EmDNAPhysics_option2.hh>
#include <G4EmDNAPhysics_option3.hh>
#include <G4EmDNAPhysics_option4.hh>
#include <G4EmDNAPhysics_option5.hh>
#include <G4EmDNAPhysics_option6.hh>
#include <G4EmDNAPhysics_option7.hh>
#include <G4EmDNAPhysics_option8.hh>
#include <G4EmDNAPhysics_stationary_option2.hh>
#include <G4EmDNAPhysics_stationary_option4.hh>
#include <G4EmDNAPhysics_stationary_option6.hh>
#include <G4EmDNAPhysics_stationary.hh>
#include <G4EmDNAPhysics.hh>
#include <G4EmDNAPhysicsActivator.hh>
#include <G4EmLivermorePhysics.hh>
#include <G4EmLivermorePolarizedPhysics.hh>
#include <G4EmLowEPPhysics.hh>
#include <G4EmPenelopePhysics.hh>
#include <G4EmStandardPhysics_option1.hh>
#include <G4EmStandardPhysics_option2.hh>
#include <G4EmStandardPhysics_option3.hh>
#include <G4EmStandardPhysics_option4.hh>
#include <G4EmStandardPhysics.hh>
#include <G4EmStandardPhysicsGS.hh>
#include <G4EmStandardPhysicsSS.hh>
#include <G4EmStandardPhysicsWVI.hh>
#include <G4OpticalPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_EM_PHYSICS(name)                              \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

#define ADD_EM_PHYSICS_REDUCED(name) py::class_<name, G4VPhysicsConstructor>(m, #name).def(py::init<>());

void export_G4EmPhysics(py::module &m)
{
   ADD_EM_PHYSICS(G4EmDNAChemistry_option1);
   ADD_EM_PHYSICS(G4EmDNAChemistry_option2);
   ADD_EM_PHYSICS(G4EmDNAChemistry_option3);
   ADD_EM_PHYSICS(G4EmDNAChemistry);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option1);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option2);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option3);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option4);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option5);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option6);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option7);
   ADD_EM_PHYSICS(G4EmDNAPhysics_option8);
   ADD_EM_PHYSICS(G4EmDNAPhysics_stationary_option2);
   ADD_EM_PHYSICS(G4EmDNAPhysics_stationary_option4);
   ADD_EM_PHYSICS(G4EmDNAPhysics_stationary_option6);
   ADD_EM_PHYSICS(G4EmDNAPhysics_stationary);
   ADD_EM_PHYSICS(G4EmDNAPhysics);
   ADD_EM_PHYSICS(G4EmDNAPhysicsActivator);
   ADD_EM_PHYSICS(G4EmLivermorePhysics);
   ADD_EM_PHYSICS(G4EmLivermorePolarizedPhysics);
   ADD_EM_PHYSICS(G4EmLowEPPhysics);
   ADD_EM_PHYSICS(G4EmPenelopePhysics);
   ADD_EM_PHYSICS(G4EmStandardPhysics_option1);
   ADD_EM_PHYSICS(G4EmStandardPhysics_option2);
   ADD_EM_PHYSICS(G4EmStandardPhysics_option3);
   ADD_EM_PHYSICS(G4EmStandardPhysics_option4);
   ADD_EM_PHYSICS(G4EmStandardPhysics);
   ADD_EM_PHYSICS(G4EmStandardPhysicsGS);
   ADD_EM_PHYSICS(G4EmStandardPhysicsSS);
   ADD_EM_PHYSICS(G4EmStandardPhysicsWVI);
   ADD_EM_PHYSICS_REDUCED(G4OpticalPhysics);
}
