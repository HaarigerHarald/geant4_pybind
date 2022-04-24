#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define EXPORT_G4HEADER(header, mod)   \
   void export_##header(py::module &); \
   export_##header(mod)

void export_modG4event(py::module &m)
{
   EXPORT_G4HEADER(G4Event, m);
   EXPORT_G4HEADER(G4EventManager, m);
   EXPORT_G4HEADER(G4StackManager, m);
   EXPORT_G4HEADER(G4UserEventAction, m);
   EXPORT_G4HEADER(G4UserStackingAction, m);
   EXPORT_G4HEADER(G4ClassificationOfNewTrack, m);
   EXPORT_G4HEADER(G4VPrimaryGenerator, m);
   EXPORT_G4HEADER(G4ParticleGun, m);
   EXPORT_G4HEADER(G4GeneralParticleSource, m);
   EXPORT_G4HEADER(G4TrajectoryContainer, m);

   EXPORT_G4HEADER(G4GeneralParticleSourceData, m);
   EXPORT_G4HEADER(G4HEPEvtInterface, m);
   EXPORT_G4HEADER(G4HEPEvtParticle, m);
   EXPORT_G4HEADER(G4MultiEventAction, m);
   EXPORT_G4HEADER(G4PrimaryTransformer, m);
   EXPORT_G4HEADER(G4RayShooter, m);
   EXPORT_G4HEADER(G4SingleParticleSource, m);
   EXPORT_G4HEADER(G4SmartTrackStack, m);
   EXPORT_G4HEADER(G4SPSAngDistribution, m);
   EXPORT_G4HEADER(G4SPSEneDistribution, m);
   EXPORT_G4HEADER(G4SPSPosDistribution, m);
   EXPORT_G4HEADER(G4SPSRandomGenerator, m);
   EXPORT_G4HEADER(G4StackedTrack, m);
   EXPORT_G4HEADER(G4TrackStack, m);

   EXPORT_G4HEADER(G4EvManMessenger, m);
   EXPORT_G4HEADER(G4GeneralParticleSourceMessenger, m);
   EXPORT_G4HEADER(G4ParticleGunMessenger, m);
   EXPORT_G4HEADER(G4StackingMessenger, m);
}
