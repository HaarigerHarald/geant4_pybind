#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistTubsHypeSide.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TwistTubsHypeSide : public G4TwistTubsHypeSide, public py::trampoline_self_life_support {
public:
   using G4TwistTubsHypeSide::G4TwistTubsHypeSide;

   G4int GetAreaCode(const G4ThreeVector &xx, G4bool withtol) override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4TwistTubsHypeSide, GetAreaCode, xx, withtol);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector *gxx, G4double *distance,
                           G4int *areacode, G4bool *isvalid, G4VTwistSurface::EValidate validate) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsHypeSide, DistanceToSurface, gp, gv, gxx, distance, areacode, isvalid,
                        validate);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, G4ThreeVector *gxx, G4double *distance, G4int *areacode) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsHypeSide, DistanceToSurface, gp, gxx, distance, areacode);
   }

   G4ThreeVector GetNormal(const G4ThreeVector &xx, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTubsHypeSide, GetNormal, xx, isGlobal);
   }

   EInside Inside(const G4ThreeVector &gp) override { PYBIND11_OVERRIDE(EInside, G4TwistTubsHypeSide, Inside, gp); }

   G4double GetRhoAtPZ(const G4ThreeVector &p, G4bool isglobal) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistTubsHypeSide, GetRhoAtPZ, p, isglobal);
   }

   G4ThreeVector SurfacePoint(G4double arg0, G4double arg1, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTubsHypeSide, SurfacePoint, arg0, arg1, isGlobal);
   }

   G4double GetBoundaryMin(G4double phi) override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistTubsHypeSide, GetBoundaryMin, phi);
   }

   G4double GetBoundaryMax(G4double phi) override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistTubsHypeSide, GetBoundaryMax, phi);
   }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistTubsHypeSide, GetSurfaceArea, ); }

   G4int AmIOnLeftSide(const G4ThreeVector &me, const G4ThreeVector &vec, G4bool withTol) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsHypeSide, AmIOnLeftSide, me, vec, withTol);
   }

   G4double DistanceToBoundary(G4int areacode, G4ThreeVector &xx, const G4ThreeVector &p) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsHypeSide, "DistanceToBoundary", areacode, std::addressof(xx), p);
      return G4TwistTubsHypeSide::DistanceToBoundary(areacode, xx, p);
   }

   G4double DistanceToIn(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsHypeSide, "DistanceToIn", gp, gv, std::addressof(gxxbest));
      return G4TwistTubsHypeSide::DistanceToIn(gp, gv, gxxbest);
   }

   G4double DistanceToOut(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsHypeSide, "DistanceToOut", gp, gv, std::addressof(gxxbest));
      return G4TwistTubsHypeSide::DistanceToOut(gp, gv, gxxbest);
   }

   G4double DistanceTo(const G4ThreeVector &gp, G4ThreeVector &gxx) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsHypeSide, "DistanceTo", gp, std::addressof(gxx));
      return G4TwistTubsHypeSide::DistanceTo(gp, gxx);
   }

   G4String GetName() const override { PYBIND11_OVERRIDE(G4String, G4TwistTubsHypeSide, GetName, ); }

   void GetBoundaryParameters(const G4int &areacode, G4ThreeVector &d, G4ThreeVector &x0,
                              G4int &boundarytype) const override
   {
      PYBIND11_OVERRIDE(void, G4TwistTubsHypeSide, GetBoundaryParameters, areacode, d, x0, boundarytype);
   }

   G4ThreeVector GetBoundaryAtPZ(G4int areacode, const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTubsHypeSide, GetBoundaryAtPZ, areacode, p);
   }

   void SetBoundary(const G4int &axiscode, const G4ThreeVector &direction, const G4ThreeVector &x0,
                    const G4int &boundarytype) override
   {
      PYBIND11_OVERRIDE(void, G4TwistTubsHypeSide, SetBoundary, axiscode, direction, x0, boundarytype);
   }
};

void export_G4TwistTubsHypeSide(py::module &m)
{
   py::class_<G4TwistTubsHypeSide, PyG4TwistTubsHypeSide, G4VTwistSurface>(m, "G4TwistTubsHypeSide")

      .def(py::init<const G4String &, const G4RotationMatrix &, const G4ThreeVector &, const G4int, const G4double,
                    const G4double, const G4double, const EAxis, const EAxis, G4double, G4double, G4double, G4double>(),
           py::arg("name"), py::arg("rot"), py::arg("tlate"), py::arg("handedness"), py::arg("kappa"),
           py::arg("tanstereo"), py::arg("r0"), py::arg("axis0") = kPhi, py::arg("axis1") = kZAxis,
           py::arg("axis0min") = -kInfinity, py::arg("axis1min") = -kInfinity, py::arg("axis0max") = kInfinity,
           py::arg("axis1max") = kInfinity)

      .def(py::init<const G4String &, G4double *, G4double *, G4double, G4double *, G4double *, G4double, G4double,
                    G4double, G4double, G4double, G4int>(),
           py::arg("name"), py::arg("EndInnerRadius"), py::arg("EndOuterRadius"), py::arg("DPhi"), py::arg("EndPhi"),
           py::arg("EndZ"), py::arg("InnerRadius"), py::arg("OuterRadius"), py::arg("Kappa"), py::arg("TanInnerStereo"),
           py::arg("TanOuterStereo"), py::arg("handedness"))

      .def("__copy__", [](const PyG4TwistTubsHypeSide &self) { return PyG4TwistTubsHypeSide(self); })
      .def("__deepcopy__", [](const PyG4TwistTubsHypeSide &self, py::dict) { return PyG4TwistTubsHypeSide(self); })
      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *,
                             G4bool *, G4VTwistSurface::EValidate>(&G4TwistTubsHypeSide::DistanceToSurface),
           py::arg("gp"), py::arg("gv"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"), py::arg("isvalid"),
           py::arg("validate") = G4VTwistSurface::kValidateWithTol)

      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *>(
              &G4TwistTubsHypeSide::DistanceToSurface),
           py::arg("gp"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"))

      .def("GetNormal", &G4TwistTubsHypeSide::GetNormal, py::arg("xx"), py::arg("isGlobal") = false)
      .def("Inside", &G4TwistTubsHypeSide::Inside, py::arg("gp"))
      .def("GetRhoAtPZ", &G4TwistTubsHypeSide::GetRhoAtPZ, py::arg("p"), py::arg("isglobal") = false)
      .def("SurfacePoint", &G4TwistTubsHypeSide::SurfacePoint, py::arg("arg0"), py::arg("arg1"),
           py::arg("isGlobal") = false)

      .def("GetBoundaryMin", &G4TwistTubsHypeSide::GetBoundaryMin, py::arg("phi"))
      .def("GetBoundaryMax", &G4TwistTubsHypeSide::GetBoundaryMax, py::arg("phi"))
      .def("GetSurfaceArea", &G4TwistTubsHypeSide::GetSurfaceArea)
      .def(
         "GetFacets",
         [](G4TwistTubsHypeSide &self, G4int m, G4int n, py::list pyXyz, py::list pyFaces, G4int iside) {
            G4double(*xyz)[3] = new G4double[pyXyz.size()][3];
            G4int(*faces)[4]  = new G4int[pyFaces.size()][4];

            for (size_t i = 0; i < pyXyz.size(); i++) {
               py::list innerList = pyXyz[i];
               for (size_t j = 0; j < 3; j++) {
                  xyz[i][j] = innerList[j].cast<G4double>();
               }
            }

            for (size_t i = 0; i < pyFaces.size(); i++) {
               py::list innerList = pyFaces[i];
               for (size_t j = 0; j < 4; j++) {
                  xyz[i][j] = innerList[j].cast<G4int>();
               }
            }

            self.GetFacets(m, n, xyz, faces, iside);

            delete[] xyz;
            delete[] faces;
         },
         py::arg("m"), py::arg("n"), py::arg("xyz"), py::arg("faces"), py::arg("iside"));
}
