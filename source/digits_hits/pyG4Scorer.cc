#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <G4PSCellCharge.hh>
#include <G4PSCellCharge3D.hh>
#include <G4PSCellFlux.hh>
#include <G4PSCellFlux3D.hh>
#include <G4PSCellFluxForCylinder3D.hh>
#include <G4PSCylinderSurfaceCurrent.hh>
#include <G4PSCylinderSurfaceCurrent3D.hh>
#include <G4PSCylinderSurfaceFlux.hh>
#include <G4PSCylinderSurfaceFlux3D.hh>
#include <G4PSDirectionFlag.hh>
#include <G4PSDoseDeposit.hh>
#include <G4PSDoseDeposit3D.hh>
#include <G4PSDoseDepositForCylinder3D.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4PSEnergyDeposit3D.hh>
#include <G4PSFlatSurfaceCurrent.hh>
#include <G4PSFlatSurfaceCurrent3D.hh>
#include <G4PSFlatSurfaceFlux.hh>
#include <G4PSFlatSurfaceFlux3D.hh>
#include <G4PSMinKinEAtGeneration.hh>
#include <G4PSMinKinEAtGeneration3D.hh>
#include <G4PSNofCollision.hh>
#include <G4PSNofCollision3D.hh>
#include <G4PSNofSecondary.hh>
#include <G4PSNofSecondary3D.hh>
#include <G4PSNofStep.hh>
#include <G4PSNofStep3D.hh>
#include <G4PSPassageCellCurrent.hh>
#include <G4PSPassageCellCurrent3D.hh>
#include <G4PSPassageCellFlux.hh>
#include <G4PSPassageCellFlux3D.hh>
#include <G4PSPassageCellFluxForCylinder3D.hh>
#include <G4PSPassageTrackLength.hh>
#include <G4PSPassageTrackLength3D.hh>
#include <G4PSPopulation.hh>
#include <G4PSPopulation3D.hh>
#include <G4PSSphereSurfaceCurrent.hh>
#include <G4PSSphereSurfaceCurrent3D.hh>
#include <G4PSSphereSurfaceFlux.hh>
#include <G4PSSphereSurfaceFlux3D.hh>
#include <G4PSStepChecker.hh>
#include <G4PSStepChecker3D.hh>
#include <G4PSTermination.hh>
#include <G4PSTermination3D.hh>
#include <G4PSTrackCounter.hh>
#include <G4PSTrackCounter3D.hh>
#include <G4PSTrackLength.hh>
#include <G4PSTrackLength3D.hh>
#include <G4PSVolumeFlux.hh>
#include <G4PSVolumeFlux3D.hh>
#include <G4SDChargedFilter.hh>
#include <G4SDKineticEnergyFilter.hh>
#include <G4SDNeutralFilter.hh>
#include <G4SDParticleFilter.hh>
#include <G4SDParticleWithEnergyFilter.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4Scorer(py::module &m)
{
   py::class_<G4THitsMap<double>, G4VHitsCollection, owntrans_ptr<G4THitsMap<double>>>(m, "G4DoubleHitsMap")
      .def(py::init<>())
      .def(py::init<G4String, G4String>())
      .def(py::self == py::self)

      .def("DrawAllHits", &G4THitsMap<double>::DrawAllHits)
      .def("PrintAllHits", &G4THitsMap<double>::PrintAllHits)

      .def(
         "__getitem__", [](G4THitsMap<double> &self, std::size_t n) { return self[n]; }, py::is_operator(),
         py::return_value_policy::reference_internal)

      .def("entries", &G4THitsMap<double>::entries)
      .def("GetHit", &G4THitsMap<double>::GetHit, py::return_value_policy::reference_internal)
      .def("GetSize", &G4THitsMap<double>::GetSize)

      .def(
         "__iter__", [](const G4THitsMap<double> &s) { return py::make_iterator(s.begin(), s.end()); },
         py::keep_alive<0, 1>());

   py::class_<G4PSDoseDeposit, G4VPrimitivePlotter, owntrans_ptr<G4PSDoseDeposit>>(m, "G4PSDoseDeposit")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0);

   py::class_<G4PSEnergyDeposit, G4VPrimitivePlotter, owntrans_ptr<G4PSEnergyDeposit>>(m, "G4PSEnergyDeposit")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0);

   // TODO add all other scorers
}
