#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVParameterised.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

#include "../management/pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class G4PVParameterisedSharedResources : public G4PVParameterised, public SharedPhysicalVolumeRotation {
public:
   G4PVParameterisedSharedResources(const G4String &pName, G4LogicalVolume *pLogical, G4LogicalVolume *pMotherLogical,
                                    const EAxis pAxis, const G4int nReplicas,
                                    std::shared_ptr<G4VPVParameterisation> pParam, G4bool pSurfChk = false)
      : G4PVParameterised(pName, pLogical, pMotherLogical, pAxis, nReplicas, pParam.get(), pSurfChk)
   {
      sharedParametrisation = pParam;
   }

   G4PVParameterisedSharedResources(const G4String &pName, G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother,
                                    const EAxis pAxis, const G4int nReplicas,
                                    std::shared_ptr<G4VPVParameterisation> pParam, G4bool pSurfChk = false)
      : G4PVParameterised(pName, pLogical, pMother, pAxis, nReplicas, pParam.get(), pSurfChk)
   {
      sharedParametrisation = pParam;
   }

   std::shared_ptr<G4VPVParameterisation> sharedParametrisation;
};

class PyG4PVParameterised : public G4PVParameterisedSharedResources, public py::trampoline_self_life_support {
public:
   using G4PVParameterisedSharedResources::G4PVParameterisedSharedResources;

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE(G4bool, G4PVParameterised, IsParameterised, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE(G4VPVParameterisation *, G4PVParameterised, GetParameterisation, );
   }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE(void, G4PVParameterised, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   void SetRegularStructureId(G4int code) override
   {
      PYBIND11_OVERRIDE(void, G4PVParameterised, SetRegularStructureId, code);
   }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int maxErr) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PVParameterised, CheckOverlaps, res, tol, verbose, maxErr);
   }

   G4bool IsMany() const override { PYBIND11_OVERRIDE(G4bool, G4PVParameterised, IsMany, ); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE(G4bool, G4PVParameterised, IsReplicated, ); }

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE(G4int, G4PVParameterised, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE(void, G4PVParameterised, SetCopyNo, CopyNo); }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4PVParameterised, GetMultiplicity, ); }

   G4bool IsRegularStructure() const override { PYBIND11_OVERRIDE(G4bool, G4PVParameterised, IsRegularStructure, ); }

   G4int GetRegularStructureId() const override
   {
      PYBIND11_OVERRIDE(G4int, G4PVParameterised, GetRegularStructureId, );
   }
};

void export_G4PVParameterised(py::module &m)
{
   py::class_<G4PVParameterisedSharedResources, PyG4PVParameterised, G4PVReplica, py::nodelete>(m, "G4PVParameterised")

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                    std::shared_ptr<G4VPVParameterisation>, G4bool>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("pParam"), py::arg("pSurfChk") = false)

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int,
                    std::shared_ptr<G4VPVParameterisation>, G4bool>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("pParam"), py::arg("pSurfChk") = false)

      .def("IsParameterised", &G4PVParameterised::IsParameterised)
      .def("VolumeType", &G4PVParameterised::VolumeType)
      .def("GetParameterisation", &G4PVParameterised::GetParameterisation, py::return_value_policy::reference)
      .def("GetReplicationData", &G4PVParameterised::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("SetRegularStructureId", &G4PVParameterised::SetRegularStructureId, py::arg("code"))
      .def("CheckOverlaps", &G4PVParameterised::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.,
           py::arg("verbose") = true, py::arg("maxErr") = 1);
}
