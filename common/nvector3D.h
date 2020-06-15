/****************************************************************************
 **
 **  Copyright (C) 2015 Andreas Mussgiller
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 **
 ****************************************************************************/

#ifndef NVECTOR3D_H
#define NVECTOR3D_H

#include <iostream>

class NPoint3D;

/** @addtogroup common
 *  @{
 */

class NVector3D
{
public:

  NVector3D();
  NVector3D(double x, double y, double z);
  NVector3D(const NPoint3D& a, const NPoint3D& b);
  NVector3D(const NVector3D& other);
  ~NVector3D();

  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }

  void rotateX(double angle);
  void rotateY(double angle);
  void rotateZ(double angle);

  double length() const;
  double dot(const NVector3D& other) const;
  NVector3D cross(const NVector3D& other);

  NVector3D operator+(const NVector3D& other);
  NVector3D operator-(const NVector3D& other);

  NVector3D& operator+=(const NVector3D& other);
  NVector3D& operator-=(const NVector3D& other);

  NVector3D& operator*=(const double scale);

  void print();

protected:

  double x_, y_, z_;
};

/** @} */

#endif // NVECTOR3D_H
