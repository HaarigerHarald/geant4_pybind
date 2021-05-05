#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TrackingManager(py::module &);
void export_G4UserSteppingAction(py::module &);
void export_G4UserTrackingAction(py::module &);
void export_G4VTrajectoryPoint(py::module &);
void export_G4TrajectoryPoint(py::module &);
void export_G4VTrajectory(py::module &);
void export_G4Trajectory(py::module &);
void export_G4VSteppingVerbose(py::module &);
void export_G4SteppingVerbose(py::module &);

void export_modG4tracking(py::module &m)
{
   export_G4TrackingManager(m);
   export_G4UserSteppingAction(m);
   export_G4UserTrackingAction(m);
   export_G4VTrajectoryPoint(m);
   export_G4TrajectoryPoint(m);
   export_G4VTrajectory(m);
   export_G4Trajectory(m);
   export_G4VSteppingVerbose(m);
   export_G4SteppingVerbose(m);
}
