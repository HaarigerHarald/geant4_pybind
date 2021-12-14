#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
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

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Scorer(py::module &m)
{
   py::class_<G4THitsMap<double>, G4VHitsCollection>(m, "G4DoubleHitsMap")
      .def(py::init<>())
      .def(py::init<G4String, G4String>())
      .def(py::self == py::self)

      .def("DrawAllHits", &G4THitsMap<double>::DrawAllHits)
      .def("PrintAllHits", &G4THitsMap<double>::PrintAllHits)

      .def(
         "__getitem__", [](const G4THitsMap<double> &self, std::size_t n) { return self[n]; }, py::is_operator(),
         py::return_value_policy::reference_internal)

      .def("entries", &G4THitsMap<double>::entries)
      .def("GetHit", &G4THitsMap<double>::GetHit, py::return_value_policy::reference_internal)
      .def("GetSize", &G4THitsMap<double>::GetSize)

      .def(
         "__iter__", [](const G4THitsMap<double> &s) { return py::make_iterator(s.begin(), s.end()); },
         py::keep_alive<0, 1>(), py::is_operator());

   py::class_<G4PSCellCharge, G4VPrimitiveScorer>(m, "G4PSCellCharge")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0);

   py::class_<G4PSCellCharge3D, G4PSCellCharge>(m, "G4PSCellCharge3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSCellFlux, G4VPrimitivePlotter>(m, "G4PSCellFlux")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0);

   py::class_<G4PSCellFlux3D, G4PSCellFlux>(m, "G4PSCellFlux3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSCellFluxForCylinder3D, G4PSCellFlux>(m, "G4PSCellFluxForCylinder3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0)

      .def("SetCylinderSize", &G4PSCellFluxForCylinder3D::SetCylinderSize, py::arg("cylSize"), py::arg("startAng"),
           py::arg("angSpan"))

      .def("SetNumberOfSegments",
           [](G4PSCellFluxForCylinder3D &self, G4int z, G4int phi, G4int r) {
              G4int nSeg[] = {z, phi, r};
              self.SetNumberOfSegments(nSeg);
           })
      .def("SetNumberOfSegments", [](G4PSCellFluxForCylinder3D &self, py::list list) {
         G4int nSeg[3];
         for (size_t i = 0; i < 3; i++) {
            nSeg[i] = list[i].cast<G4int>();
         }
         self.SetNumberOfSegments(nSeg);
      });

   py::class_<G4PSCylinderSurfaceCurrent, G4VPrimitivePlotter>(m, "G4PSCylinderSurfaceCurrent")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSCylinderSurfaceCurrent::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSCylinderSurfaceCurrent::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSCylinderSurfaceCurrent::Initialize)
      .def("EndOfEvent", &G4PSCylinderSurfaceCurrent::EndOfEvent)
      .def("clear", &G4PSCylinderSurfaceCurrent::clear)
      .def("DrawAll", &G4PSCylinderSurfaceCurrent::DrawAll)
      .def("PrintAll", &G4PSCylinderSurfaceCurrent::PrintAll)
      .def("SetUnit", &G4PSCylinderSurfaceCurrent::SetUnit, py::arg("unit"));

   py::class_<G4PSCylinderSurfaceCurrent3D, G4PSCylinderSurfaceCurrent>(m, "G4PSCylinderSurfaceCurrent3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSCylinderSurfaceFlux, G4VPrimitivePlotter>(m, "G4PSCylinderSurfaceFlux")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSCylinderSurfaceFlux::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSCylinderSurfaceFlux::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSCylinderSurfaceFlux::Initialize)
      .def("EndOfEvent", &G4PSCylinderSurfaceFlux::EndOfEvent)
      .def("clear", &G4PSCylinderSurfaceFlux::clear)
      .def("DrawAll", &G4PSCylinderSurfaceFlux::DrawAll)
      .def("PrintAll", &G4PSCylinderSurfaceFlux::PrintAll)
      .def("SetUnit", &G4PSCylinderSurfaceFlux::SetUnit, py::arg("unit"));

   py::class_<G4PSCylinderSurfaceFlux3D, G4PSCylinderSurfaceFlux>(m, "G4PSCylinderSurfaceFlux3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::enum_<G4PSFluxFlag>(m, "G4PSFluxFlag")
      .value("fFlux_InOut", fFlux_InOut)
      .value("fFlux_In", fFlux_In)
      .value("fFlux_Out", fFlux_Out)
      .export_values();

   py::enum_<G4PSCurrentFlag>(m, "G4PSCurrentFlag")
      .value("fCurrent_InOut", fCurrent_InOut)
      .value("fCurrent_In", fCurrent_In)
      .value("fCurrent_Out", fCurrent_Out)
      .export_values();

   py::class_<G4PSDoseDeposit, G4VPrimitivePlotter>(m, "G4PSDoseDeposit")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)
      .def("Initialize", &G4PSDoseDeposit::Initialize)
      .def("EndOfEvent", &G4PSDoseDeposit::EndOfEvent)
      .def("clear", &G4PSDoseDeposit::clear)
      .def("DrawAll", &G4PSDoseDeposit::DrawAll)
      .def("PrintAll", &G4PSDoseDeposit::PrintAll)
      .def("SetUnit", &G4PSDoseDeposit::SetUnit, py::arg("unit"));

   py::class_<G4PSDoseDeposit3D, G4PSDoseDeposit>(m, "G4PSDoseDeposit3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSDoseDepositForCylinder3D, G4PSDoseDeposit3D>(m, "G4PSDoseDepositForCylinder3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0)

      .def("SetCylinderSize", &G4PSDoseDepositForCylinder3D::SetCylinderSize, py::arg("cylSize"), py::arg("startAng"),
           py::arg("angSpan"))

      .def("SetNumberOfSegments",
           [](G4PSDoseDepositForCylinder3D &self, G4int z, G4int phi, G4int r) {
              G4int nSeg[] = {z, phi, r};
              self.SetNumberOfSegments(nSeg);
           })
      .def("SetNumberOfSegments", [](G4PSDoseDepositForCylinder3D &self, py::list list) {
         G4int nSeg[3];
         for (size_t i = 0; i < 3; i++) {
            nSeg[i] = list[i].cast<G4int>();
         }
         self.SetNumberOfSegments(nSeg);
      });

   py::class_<G4PSEnergyDeposit, G4VPrimitivePlotter>(m, "G4PSEnergyDeposit")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)
      .def("Initialize", &G4PSEnergyDeposit::Initialize)
      .def("EndOfEvent", &G4PSEnergyDeposit::EndOfEvent)
      .def("clear", &G4PSEnergyDeposit::clear)
      .def("DrawAll", &G4PSEnergyDeposit::DrawAll)
      .def("PrintAll", &G4PSEnergyDeposit::PrintAll)
      .def("SetUnit", &G4PSEnergyDeposit::SetUnit, py::arg("unit"));

   py::class_<G4PSEnergyDeposit3D, G4PSEnergyDeposit>(m, "G4PSEnergyDeposit3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSFlatSurfaceCurrent, G4VPrimitivePlotter>(m, "G4PSFlatSurfaceCurrent")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSFlatSurfaceCurrent::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSFlatSurfaceCurrent::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSFlatSurfaceCurrent::Initialize)
      .def("EndOfEvent", &G4PSFlatSurfaceCurrent::EndOfEvent)
      .def("clear", &G4PSFlatSurfaceCurrent::clear)
      .def("DrawAll", &G4PSFlatSurfaceCurrent::DrawAll)
      .def("PrintAll", &G4PSFlatSurfaceCurrent::PrintAll)
      .def("SetUnit", &G4PSFlatSurfaceCurrent::SetUnit, py::arg("unit"));

   py::class_<G4PSFlatSurfaceCurrent3D, G4PSFlatSurfaceCurrent>(m, "G4PSFlatSurfaceCurrent3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSFlatSurfaceFlux, G4VPrimitivePlotter>(m, "G4PSFlatSurfaceFlux")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSFlatSurfaceFlux::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSFlatSurfaceFlux::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSFlatSurfaceFlux::Initialize)
      .def("EndOfEvent", &G4PSFlatSurfaceFlux::EndOfEvent)
      .def("clear", &G4PSFlatSurfaceFlux::clear)
      .def("DrawAll", &G4PSFlatSurfaceFlux::DrawAll)
      .def("PrintAll", &G4PSFlatSurfaceFlux::PrintAll)
      .def("SetUnit", &G4PSFlatSurfaceFlux::SetUnit, py::arg("unit"));

   py::class_<G4PSFlatSurfaceFlux3D, G4PSFlatSurfaceFlux>(m, "G4PSFlatSurfaceFlux3D")

      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSMinKinEAtGeneration, G4VPrimitivePlotter>(m, "G4PSMinKinEAtGeneration")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)
      .def("Initialize", &G4PSMinKinEAtGeneration::Initialize)
      .def("EndOfEvent", &G4PSMinKinEAtGeneration::EndOfEvent)
      .def("clear", &G4PSMinKinEAtGeneration::clear)
      .def("DrawAll", &G4PSMinKinEAtGeneration::DrawAll)
      .def("PrintAll", &G4PSMinKinEAtGeneration::PrintAll)
      .def("SetUnit", &G4PSMinKinEAtGeneration::SetUnit, py::arg("unit"));

   py::class_<G4PSMinKinEAtGeneration3D, G4PSMinKinEAtGeneration>(m, "G4PSMinKinEAtGeneration3D")

      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSNofCollision, G4VPrimitiveScorer>(m, "G4PSNofCollision")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def("Weighted", &G4PSNofCollision::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSNofCollision::Initialize)
      .def("EndOfEvent", &G4PSNofCollision::EndOfEvent)
      .def("clear", &G4PSNofCollision::clear)
      .def("DrawAll", &G4PSNofCollision::DrawAll)
      .def("PrintAll", &G4PSNofCollision::PrintAll)
      .def("SetUnit", &G4PSNofCollision::SetUnit, py::arg("unit"));

   py::class_<G4PSNofCollision3D, G4PSNofCollision>(m, "G4PSNofCollision3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSNofSecondary, G4VPrimitivePlotter>(m, "G4PSNofSecondary")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)

      .def("SetParticle", &G4PSNofSecondary::SetParticle, py::arg("particleName"))
      .def("Weighted", &G4PSNofSecondary::Weighted, py::arg("flg") = true)

      .def("Initialize", &G4PSNofSecondary::Initialize)
      .def("EndOfEvent", &G4PSNofSecondary::EndOfEvent)
      .def("clear", &G4PSNofSecondary::clear)
      .def("DrawAll", &G4PSNofSecondary::DrawAll)
      .def("PrintAll", &G4PSNofSecondary::PrintAll)
      .def("SetUnit", &G4PSNofSecondary::SetUnit, py::arg("unit"));

   py::class_<G4PSNofSecondary3D, G4PSNofSecondary>(m, "G4PSNofSecondary3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSNofStep, G4VPrimitivePlotter>(m, "G4PSNofStep")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def("SetBoundaryFlag", &G4PSNofStep::SetBoundaryFlag, py::arg("flg") = true)
      .def("Initialize", &G4PSNofStep::Initialize)
      .def("EndOfEvent", &G4PSNofStep::EndOfEvent)
      .def("clear", &G4PSNofStep::clear)
      .def("DrawAll", &G4PSNofStep::DrawAll)
      .def("PrintAll", &G4PSNofStep::PrintAll)
      .def("SetUnit", &G4PSNofStep::SetUnit, py::arg("unit"));

   py::class_<G4PSNofStep3D, G4PSNofStep>(m, "G4PSNofStep3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSPassageCellCurrent, G4VPrimitivePlotter>(m, "G4PSPassageCellCurrent")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)

      .def("Weighted", &G4PSPassageCellCurrent::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSPassageCellCurrent::Initialize)
      .def("EndOfEvent", &G4PSPassageCellCurrent::EndOfEvent)
      .def("clear", &G4PSPassageCellCurrent::clear)
      .def("DrawAll", &G4PSPassageCellCurrent::DrawAll)
      .def("PrintAll", &G4PSPassageCellCurrent::PrintAll)
      .def("SetUnit", &G4PSPassageCellCurrent::SetUnit, py::arg("unit"));

   py::class_<G4PSPassageCellCurrent3D, G4PSPassageCellCurrent>(m, "G4PSPassageCellCurrent3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSPassageCellFlux, G4VPrimitivePlotter>(m, "G4PSPassageCellFlux")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)

      .def("Weighted", &G4PSPassageCellFlux::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSPassageCellFlux::Initialize)
      .def("EndOfEvent", &G4PSPassageCellFlux::EndOfEvent)
      .def("clear", &G4PSPassageCellFlux::clear)
      .def("DrawAll", &G4PSPassageCellFlux::DrawAll)
      .def("PrintAll", &G4PSPassageCellFlux::PrintAll)
      .def("SetUnit", &G4PSPassageCellFlux::SetUnit, py::arg("unit"));

   py::class_<G4PSPassageCellFlux3D, G4PSPassageCellFlux>(m, "G4PSPassageCellFlux3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)
      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSPassageCellFluxForCylinder3D, G4PSPassageCellFlux3D>(m, "G4PSPassageCellFluxForCylinder3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)

      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0)

      .def("SetCylinderSize", &G4PSPassageCellFluxForCylinder3D::SetCylinderSize, py::arg("cylSize"),
           py::arg("startAng"), py::arg("angSpan"))

      .def("SetNumberOfSegments",
           [](G4PSPassageCellFluxForCylinder3D &self, G4int z, G4int phi, G4int r) {
              G4int nSeg[] = {z, phi, r};
              self.SetNumberOfSegments(nSeg);
           })
      .def("SetNumberOfSegments", [](G4PSPassageCellFluxForCylinder3D &self, py::list list) {
         G4int nSeg[3];
         for (size_t i = 0; i < 3; i++) {
            nSeg[i] = list[i].cast<G4int>();
         }
         self.SetNumberOfSegments(nSeg);
      });

   py::class_<G4PSPassageTrackLength, G4VPrimitivePlotter>(m, "G4PSPassageTrackLength")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)
      .def("Weighted", &G4PSPassageTrackLength::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSPassageTrackLength::Initialize)
      .def("EndOfEvent", &G4PSPassageTrackLength::EndOfEvent)
      .def("clear", &G4PSPassageTrackLength::clear)
      .def("DrawAll", &G4PSPassageTrackLength::DrawAll)
      .def("PrintAll", &G4PSPassageTrackLength::PrintAll)
      .def("SetUnit", &G4PSPassageTrackLength::SetUnit, py::arg("unit"));

   py::class_<G4PSPassageTrackLength3D, G4PSPassageTrackLength>(m, "G4PSPassageTrackLength3D")

      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)
      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSPopulation, G4VPrimitiveScorer>(m, "G4PSPopulation")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def("Weighted", &G4PSPopulation::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSPopulation::Initialize)
      .def("EndOfEvent", &G4PSPopulation::EndOfEvent)
      .def("clear", &G4PSPopulation::clear)
      .def("DrawAll", &G4PSPopulation::DrawAll)
      .def("PrintAll", &G4PSPopulation::PrintAll)
      .def("SetUnit", &G4PSPopulation::SetUnit, py::arg("unit"));

   py::class_<G4PSPopulation3D, G4PSPopulation>(m, "G4PSPopulation3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSSphereSurfaceCurrent, G4VPrimitiveScorer>(m, "G4PSSphereSurfaceCurrent")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)
      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSSphereSurfaceCurrent::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSSphereSurfaceCurrent::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSSphereSurfaceCurrent::Initialize)
      .def("EndOfEvent", &G4PSSphereSurfaceCurrent::EndOfEvent)
      .def("clear", &G4PSSphereSurfaceCurrent::clear)
      .def("DrawAll", &G4PSSphereSurfaceCurrent::DrawAll)
      .def("PrintAll", &G4PSSphereSurfaceCurrent::PrintAll)
      .def("SetUnit", &G4PSSphereSurfaceCurrent::SetUnit, py::arg("unit"));

   py::class_<G4PSSphereSurfaceCurrent3D, G4PSSphereSurfaceCurrent>(m, "G4PSSphereSurfaceCurrent3D")

      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSSphereSurfaceFlux, G4VPrimitiveScorer>(m, "G4PSSphereSurfaceFlux")

      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)
      .def(py::init<G4String, G4int, const G4String &, G4int>(), py::arg("name"), py::arg("direction"), py::arg("unit"),
           py::arg("depth") = 0)

      .def("Weighted", &G4PSSphereSurfaceFlux::Weighted, py::arg("flg") = true)
      .def("DivideByArea", &G4PSSphereSurfaceFlux::DivideByArea, py::arg("flg") = true)
      .def("Initialize", &G4PSSphereSurfaceFlux::Initialize)
      .def("EndOfEvent", &G4PSSphereSurfaceFlux::EndOfEvent)
      .def("clear", &G4PSSphereSurfaceFlux::clear)
      .def("DrawAll", &G4PSSphereSurfaceFlux::DrawAll)
      .def("PrintAll", &G4PSSphereSurfaceFlux::PrintAll)
      .def("SetUnit", &G4PSSphereSurfaceFlux::SetUnit, py::arg("unit"));

   py::class_<G4PSSphereSurfaceFlux3D, G4PSSphereSurfaceFlux>(m, "G4PSSphereSurfaceFlux3D")

      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0)

      .def(py::init<G4String, G4int, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction"), py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1,
           py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSStepChecker, G4VPrimitiveScorer>(m, "G4PSStepChecker")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def("Initialize", &G4PSStepChecker::Initialize)
      .def("EndOfEvent", &G4PSStepChecker::EndOfEvent)
      .def("clear", &G4PSStepChecker::clear)
      .def("DrawAll", &G4PSStepChecker::DrawAll)
      .def("PrintAll", &G4PSStepChecker::PrintAll);

   py::class_<G4PSStepChecker3D, G4PSStepChecker>(m, "G4PSStepChecker3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSTermination, G4VPrimitiveScorer>(m, "G4PSTermination")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def("Weighted", &G4PSTermination::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSTermination::Initialize)
      .def("EndOfEvent", &G4PSTermination::EndOfEvent)
      .def("clear", &G4PSTermination::clear)
      .def("DrawAll", &G4PSTermination::DrawAll)
      .def("PrintAll", &G4PSTermination::PrintAll);

   py::class_<G4PSTermination3D, G4PSTermination>(m, "G4PSTermination3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSTrackCounter, G4VPrimitivePlotter>(m, "G4PSTrackCounter")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction"), py::arg("depth") = 0)
      .def("Weighted", &G4PSTrackCounter::Weighted, py::arg("flg") = true)
      .def("Initialize", &G4PSTrackCounter::Initialize)
      .def("EndOfEvent", &G4PSTrackCounter::EndOfEvent)
      .def("clear", &G4PSTrackCounter::clear)
      .def("DrawAll", &G4PSTrackCounter::DrawAll)
      .def("PrintAll", &G4PSTrackCounter::PrintAll)
      .def("SetUnit", &G4PSTrackCounter::SetUnit, py::arg("unit"));

   py::class_<G4PSTrackCounter3D, G4PSTrackCounter>(m, "G4PSTrackCounter3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("direction"),
           py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1,
           py::arg("depk") = 0);

   py::class_<G4PSTrackLength, G4VPrimitiveScorer>(m, "G4PSTrackLength")
      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)
      .def(py::init<G4String, const G4String &, G4int>(), py::arg("name"), py::arg("unit"), py::arg("depth") = 0)
      .def("Weighted", &G4PSTrackLength::Weighted, py::arg("flg") = true)
      .def("MultiplyKineticEnergy", &G4PSTrackLength::MultiplyKineticEnergy, py::arg("flg") = true)
      .def("DivideByVelocity", &G4PSTrackLength::DivideByVelocity, py::arg("flg") = true)
      .def("Initialize", &G4PSTrackLength::Initialize)
      .def("EndOfEvent", &G4PSTrackLength::EndOfEvent)
      .def("clear", &G4PSTrackLength::clear)
      .def("DrawAll", &G4PSTrackLength::DrawAll)
      .def("PrintAll", &G4PSTrackLength::PrintAll)
      .def("SetUnit", &G4PSTrackLength::SetUnit, py::arg("unit"));

   py::class_<G4PSTrackLength3D, G4PSTrackLength>(m, "G4PSTrackLength3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"), py::arg("ni") = 1,
           py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2, py::arg("depj") = 1, py::arg("depk") = 0)
      .def(py::init<G4String, const G4String &, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("unit"), py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);

   py::class_<G4PSVolumeFlux, G4VPrimitivePlotter>(m, "G4PSVolumeFlux")
      .def(py::init<G4String, G4int, G4int>(), py::arg("name"), py::arg("direction") = 1, py::arg("depth") = 0)
      .def("SetDivAre", &G4PSVolumeFlux::SetDivAre, py::arg("val"))
      .def("SetDivCos", &G4PSVolumeFlux::SetDivCos, py::arg("val"))
      .def("Initialize", &G4PSVolumeFlux::Initialize)
      .def("EndOfEvent", &G4PSVolumeFlux::EndOfEvent)
      .def("clear", &G4PSVolumeFlux::clear)
      .def("DrawAll", &G4PSVolumeFlux::DrawAll)
      .def("PrintAll", &G4PSVolumeFlux::PrintAll);

   py::class_<G4PSVolumeFlux3D, G4PSVolumeFlux>(m, "G4PSVolumeFlux3D")
      .def(py::init<G4String, G4int, G4int, G4int, G4int, G4int, G4int, G4int>(), py::arg("name"),
           py::arg("direction") = 1, py::arg("ni") = 1, py::arg("nj") = 1, py::arg("nk") = 1, py::arg("depi") = 2,
           py::arg("depj") = 1, py::arg("depk") = 0);
}
