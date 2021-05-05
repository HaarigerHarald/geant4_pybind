#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EventManager(py::module &);
void export_G4StackManager(py::module &);
void export_G4Event(py::module &);
void export_G4UserEventAction(py::module &);
void export_G4UserStackingAction(py::module &);
void export_G4ClassificationOfNewTrack(py::module &);
void export_G4ParticleGun(py::module &);
void export_G4TrajectoryContainer(py::module &);
void export_G4VPrimaryGenerator(py::module &);
void export_G4GeneralParticleSource(py::module &);

void export_modG4event(py::module &m)
{
   export_G4EventManager(m);
   export_G4StackManager(m);
   export_G4Event(m);
   export_G4UserEventAction(m);
   export_G4UserStackingAction(m);
   export_G4ClassificationOfNewTrack(m);
   export_G4ParticleGun(m);
   export_G4VPrimaryGenerator(m);
   export_G4GeneralParticleSource(m);
   export_G4TrajectoryContainer(m);
}
