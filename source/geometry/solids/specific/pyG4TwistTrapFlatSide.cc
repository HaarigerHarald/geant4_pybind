#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistTrapFlatSide.hh>
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

class PyG4TwistTrapFlatSide : public G4TwistTrapFlatSide, public py::trampoline_self_life_support {
public:
   using G4TwistTrapFlatSide::G4TwistTrapFlatSide;

   G4ThreeVector GetNormal(const G4ThreeVector &arg0, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTrapFlatSide, GetNormal, arg0, isGlobal);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector *gxx, G4double *distance,
                           G4int *areacode, G4bool *isvalid, G4VTwistSurface::EValidate validate) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTrapFlatSide, DistanceToSurface, gp, gv, gxx, distance, areacode, isvalid,
                        validate);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, G4ThreeVector *gxx, G4double *distance, G4int *areacode) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTrapFlatSide, DistanceToSurface, gp, gxx, distance, areacode);
   }

   G4ThreeVector SurfacePoint(G4double x, G4double y, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTrapFlatSide, SurfacePoint, x, y, isGlobal);
   }

   G4double GetBoundaryMin(G4double u) override { PYBIND11_OVERRIDE(G4double, G4TwistTrapFlatSide, GetBoundaryMin, u); }

   G4double GetBoundaryMax(G4double u) override { PYBIND11_OVERRIDE(G4double, G4TwistTrapFlatSide, GetBoundaryMax, u); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistTrapFlatSide, GetSurfaceArea, ); }

   G4int GetAreaCode(const G4ThreeVector &xx, G4bool withTol) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTrapFlatSide, GetAreaCode, xx, withTol);
   }

   G4int AmIOnLeftSide(const G4ThreeVector &me, const G4ThreeVector &vec, G4bool withTol) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTrapFlatSide, AmIOnLeftSide, me, vec, withTol);
   }

   G4double DistanceToBoundary(G4int areacode, G4ThreeVector &xx, const G4ThreeVector &p) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTrapFlatSide, "DistanceToBoundary", areacode, std::addressof(xx), p);
      return G4TwistTrapFlatSide::DistanceToBoundary(areacode, xx, p);
   }

   G4double DistanceToIn(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTrapFlatSide, "DistanceToIn", gp, gv, std::addressof(gxxbest));
      return G4TwistTrapFlatSide::DistanceToIn(gp, gv, gxxbest);
   }

   G4double DistanceToOut(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTrapFlatSide, "DistanceToOut", gp, gv, std::addressof(gxxbest));
      return G4TwistTrapFlatSide::DistanceToOut(gp, gv, gxxbest);
   }

   G4double DistanceTo(const G4ThreeVector &gp, G4ThreeVector &gxx) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTrapFlatSide, "DistanceTo", gp, std::addressof(gxx));
      return G4TwistTrapFlatSide::DistanceTo(gp, gxx);
   }

   G4String GetName() const override { PYBIND11_OVERRIDE(G4String, G4TwistTrapFlatSide, GetName, ); }

   void GetBoundaryParameters(const G4int &areacode, G4ThreeVector &d, G4ThreeVector &x0,
                              G4int &boundarytype) const override
   {
      PYBIND11_OVERRIDE(void, G4TwistTrapFlatSide, GetBoundaryParameters, areacode, d, x0, boundarytype);
   }

   G4ThreeVector GetBoundaryAtPZ(G4int areacode, const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTrapFlatSide, GetBoundaryAtPZ, areacode, p);
   }

   void SetBoundary(const G4int &axiscode, const G4ThreeVector &direction, const G4ThreeVector &x0,
                    const G4int &boundarytype) override
   {
      PYBIND11_OVERRIDE(void, G4TwistTrapFlatSide, SetBoundary, axiscode, direction, x0, boundarytype);
   }
};

void export_G4TwistTrapFlatSide(py::module &m)
{
   py::class_<G4TwistTrapFlatSide, PyG4TwistTrapFlatSide, G4VTwistSurface>(m, "G4TwistTrapFlatSide")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4int>(),
           py::arg("name"), py::arg("PhiTwist"), py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy"), py::arg("pDz"),
           py::arg("pAlpha"), py::arg("pPhi"), py::arg("pTheta"), py::arg("handedness"))

      .def("__copy__", [](const PyG4TwistTrapFlatSide &self) { return PyG4TwistTrapFlatSide(self); })
      .def("__deepcopy__", [](const PyG4TwistTrapFlatSide &self, py::dict) { return PyG4TwistTrapFlatSide(self); })
      .def("GetNormal", &G4TwistTrapFlatSide::GetNormal, py::arg("arg0"), py::arg("isGlobal") = false)
      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *,
                             G4bool *, G4VTwistSurface::EValidate>(&G4TwistTrapFlatSide::DistanceToSurface),
           py::arg("gp"), py::arg("gv"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"), py::arg("isvalid"),
           py::arg("validate") = G4VTwistSurface::kValidateWithTol)

      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *>(
              &G4TwistTrapFlatSide::DistanceToSurface),
           py::arg("gp"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"))

      .def("SurfacePoint", &G4TwistTrapFlatSide::SurfacePoint, py::arg("x"), py::arg("y"), py::arg("isGlobal") = false)
      .def("GetBoundaryMin", &G4TwistTrapFlatSide::GetBoundaryMin, py::arg("u"))
      .def("GetBoundaryMax", &G4TwistTrapFlatSide::GetBoundaryMax, py::arg("u"))
      .def("GetSurfaceArea", &G4TwistTrapFlatSide::GetSurfaceArea)
      .def(
         "GetFacets",
         [](G4TwistTrapFlatSide &self, G4int m, G4int n, py::list pyXyz, py::list pyFaces, G4int iside) {
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
