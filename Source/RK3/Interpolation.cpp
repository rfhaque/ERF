// Generated by Pankaj Jha on 05/31/2021
#include <RK3.H>

using namespace amrex;

Real
InterpolateDensityFromCellToFace(
  const int& i,
  const int& j,
  const int& k,
  const Array4<Real>& cons_in,
  const NextOrPrev& nextOrPrev,
  const Coord& coordDir,
  const int& spatial_order)
{
  return InterpolateFromCellOrFace(
    i, j, k, cons_in, Density_comp, nextOrPrev, coordDir, spatial_order);
}

Real
InterpolateRhoThetaFromCellToFace(
  const int& i,
  const int& j,
  const int& k,
  const Array4<Real>& cons_in,
  const NextOrPrev& nextOrPrev,
  const Coord& coordDir,
  const int& spatial_order)
{
  return InterpolateFromCellOrFace(
    i, j, k, cons_in, RhoTheta_comp, nextOrPrev, coordDir, spatial_order);
}
Real
InterpolateScalarFromCellToFace(
  const int& i,
  const int& j,
  const int& k,
  const Array4<Real>& cons_in,
  const NextOrPrev& nextOrPrev,
  const Coord& coordDir,
  const int& spatial_order)
{
  return InterpolateFromCellOrFace(
    i, j, k, cons_in, Scalar_comp, nextOrPrev, coordDir, spatial_order);
}

Real
InterpolateFromCellOrFace(
  // (i, j, k) is the reference cell index w.r.t. which a face is being considered
  const int& i, const int& j, const int& k,
  const Array4<Real>& qty,
  const int& qty_index,
  const NextOrPrev& nextOrPrev,
  const Coord& coordDir,
  const int& spatial_order)
{
  /*
   If the interpolation is to be done on face (i, j, k) which is previous to cell (i,j,k)
   in the coordinate direction,
   call as InterpolateFromCellOrFace(i, j, k, qty, qty_index, NextOrPrev::prev, ...)
   */
  /*
   If the interpolation is to be done on face (i+1, j, k), (i, j+1, k) or (i, j, k+1)
   which are next to cell (i,j,k) in the coordinate direction,
   call as InterpolateFromCellOrFace(i, j, k, qty, qty_index, NextOrPrev::next, ...)
   */
  //TODO: Update the description. This interpolation is applicable to cell- or face-centered quantities

  Real interpolatedVal = 0.0;
  if (nextOrPrev == NextOrPrev::prev) {
    /*
     w.r.t. the cell index (i, j, k), the face previous to it is the face at cell index m-1/2, where m = {i, j, k}
     Face index is (i, j, k). This means:
     Coordinates of face (i, j, k) = Coordinates of cell (i-1/2, j    , k    ) for x-dir. Face is previous to the cell.
     Coordinates of face (i, j, k) = Coordinates of cell (i    , j-1/2, k    ) for y-dir. Face is previous to the cell.
     Coordinates of face (i, j, k) = Coordinates of cell (i    , j    , k-1/2) for z-dir. Face is previous to the cell.
    */
    switch (spatial_order) {
    case 2:
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m-1/2) = q(i-1/2, j    , k    )
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i-1, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m-1/2) = q(i    , j-1/2, k    )
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i, j-1, k, qty_index));
        break;
      case Coord::z: // m = k, q(m-1/2) = q(i    , j    , k-1/2)
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i, j, k-1, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    case 4:
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m-1/2) = q(i-1/2, j    , k    )
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i-1, j, k, qty_index))
                          -(1.0/12.0)*(qty(i+1, j, k, qty_index) + qty(i-2, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m-1/2) = q(i    , j-1/2, k    )
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i, j-1, k, qty_index))
                          -(1.0/12.0)*(qty(i, j+1, k, qty_index) + qty(i, j-2, k, qty_index));
        break;
      case Coord::z: // m = k, q(m-1/2) = q(i    , j    , k-1/2)
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i, j, k-1, qty_index))
                          -(1.0/12.0)*(qty(i, j, k+1, qty_index) + qty(i, j, k-2, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    case 6: // In order to make this work 'qty' must have indices m-3 and m+2 where m = {i, j, k}
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m-1/2) = q(i-1/2, j    , k    )
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i-1, j, k, qty_index))
                          -(2.0/15.0)*(qty(i+1, j, k, qty_index) + qty(i-2, j, k, qty_index))
                          +(1.0/60.0)*(qty(i+2, j, k, qty_index) + qty(i-3, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m-1/2) = q(i    , j-1/2, k    )
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i, j-1, k, qty_index))
                          -(2.0/15.0)*(qty(i, j+1, k, qty_index) + qty(i, j-2, k, qty_index))
                          +(1.0/60.0)*(qty(i, j+2, k, qty_index) + qty(i, j-3, k, qty_index));
        break;
      case Coord::z: // m = k, q(m-1/2) = q(i    , j    , k-1/2)
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i, j, k-1, qty_index))
                          -(2.0/15.0)*(qty(i, j, k+1, qty_index) + qty(i, j, k-2, qty_index))
                          +(1.0/60.0)*(qty(i, j, k+2, qty_index) + qty(i, j, k-3, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    default:
      amrex::Abort("Error: Spatial order " + std::to_string(spatial_order) + " has not been implemented");
    }
  }
  else { // nextOrPrev == NextOrPrev::next
    /*
     w.r.t. the cell index (i, j, k), the face next to it is the face at cell index m+1/2, where m = {i, j, k}
     This means:
     Coordinates of face (i+1, j  , k  ) = Coordinates of cell (i+1/2, j    , k    ) for x-dir. Face is next to the cell.
     Coordinates of face (i  , j+1, k  ) = Coordinates of cell (i    , j+1/2, k    ) for y-dir. Face is next to the cell.
     Coordinates of face (i  , j  , k+1) = Coordinates of cell (i    , j    , k+1/2) for z-dir. Face is next to the cell.
    */
    switch (spatial_order) {
    case 2:
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m+1/2) = q(i+1/2, j    , k    )
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i+1, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m+1/2) = q(i    , j+1/2, k    )
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i, j+1, k, qty_index));
        break;
      case Coord::z: // m = k, q(m+1/2) = q(i    , j    , k+1/2)
        interpolatedVal = 0.5*(qty(i, j, k, qty_index) + qty(i, j, k+1, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    case 4:
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m+1/2) = q(i+1/2, j    , k    )
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i+1, j, k, qty_index))
                          -(1.0/12.0)*(qty(i-1, j, k, qty_index) + qty(i+2, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m+1/2) = q(i    , j+1/2, k    )
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i, j+1, k, qty_index))
                          -(1.0/12.0)*(qty(i, j-1, k, qty_index) + qty(i, j+2, k, qty_index));
        break;
      case Coord::z: // m = k, q(m+1/2) = q(i    , j    , k+1/2)
        interpolatedVal = (7.0/12.0)*(qty(i, j, k, qty_index) + qty(i, j, k+1, qty_index))
                          -(1.0/12.0)*(qty(i, j, k-1, qty_index) + qty(i, j, k+2, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    case 6: // In order to make this work 'qty' must have indices m+3 and m-2 where m = {i, j, k}
      switch (coordDir) {
        // q = qty(i, j, k, qty_index) = {rho, theta, rhoTheta, scalar, pressure, ...}
      case Coord::x: // m = i, q(m+1/2) = q(i+1/2, j    , k    )
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i+1, j, k, qty_index))
                          -(2.0/15.0)*(qty(i-1, j, k, qty_index) + qty(i+2, j, k, qty_index))
                          +(1.0/60.0)*(qty(i-2, j, k, qty_index) + qty(i+3, j, k, qty_index));
        break;
      case Coord::y: // m = j, q(m+1/2) = q(i    , j+1/2, k    )
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i, j+1, k, qty_index))
                          -(2.0/15.0)*(qty(i, j-1, k, qty_index) + qty(i, j+2, k, qty_index))
                          +(1.0/60.0)*(qty(i, j-2, k, qty_index) + qty(i, j+3, k, qty_index));
        break;
      case Coord::z: // m = k, q(m+1/2) = q(i    , j    , k+1/2)
        interpolatedVal = (37.0/60.0)*(qty(i, j, k, qty_index) + qty(i, j, k+1, qty_index))
                          -(2.0/15.0)*(qty(i, j, k-1, qty_index) + qty(i, j, k+2, qty_index))
                          +(1.0/60.0)*(qty(i, j, k-2, qty_index) + qty(i, j, k+3, qty_index));
        break;
      default:
        amrex::Abort("Error: Advection direction is unrecognized");
      }
      break;
    default:
      amrex::Abort("Error: Spatial order " + std::to_string(spatial_order) + " has not been implemented");
    }
  }

  return interpolatedVal;
}
