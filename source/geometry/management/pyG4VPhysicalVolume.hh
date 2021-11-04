#ifndef PYG4VPHYSICALVOLUME_HH
#define PYG4VPHYSICALVOLUME_HH

#include <memory>

#include <G4RotationMatrix.hh>

struct SharedPhysicalVolumeRotation {
   std::shared_ptr<G4RotationMatrix> sharedRotation;
};

#endif
