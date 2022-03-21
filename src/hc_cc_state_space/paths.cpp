/*********************************************************************
*  Copyright (c) 2017 - for information on the respective copyright
*  owner see the NOTICE file and/or the repository
*
*      https://github.com/hbanzhaf/steering_functions.git
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
*  implied. See the License for the specific language governing
*  permissions and limitations under the License.

*  This source code is derived from Continuous Curvature (CC) Steer.
*  Copyright (c) 2016, Thierry Fraichard and Institut national de
*  recherche en informatique et en automatique (Inria), licensed under
*  the BSD license, cf. 3rd-party-licenses.txt file in the root
*  directory of this source tree.
**********************************************************************/

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "steering_functions/hc_cc_state_space/paths.hpp"
#include "steering_functions/utilities/utilities.hpp"

using namespace std;

namespace steering
{

Path::Path(const Configuration &_start, const Configuration &_end, double _kappa, double _sigma, double _length)
{
  start = _start;
  end = _end;
  kappa = _kappa;
  sigma = _sigma;
  length = _length;
}

CC_Dubins_Path::CC_Dubins_Path(const Configuration &_start, const Configuration &_end, cc_dubins::path_type _type,
                               double _kappa, double _sigma, Configuration *_qi1, Configuration *_qi2,
                               Configuration *_qi3, Configuration *_qi4, HC_CC_Circle *_cstart, HC_CC_Circle *_cend,
                               HC_CC_Circle *_ci1, HC_CC_Circle *_ci2, double _length)
  : Path(_start, _end, _kappa, _sigma, _length)
{
  type = _type;
  qi1 = _qi1;
  qi2 = _qi2;
  qi3 = _qi3;
  qi4 = _qi4;
  cstart = _cstart;
  cend = _cend;
  ci1 = _ci1;
  ci2 = _ci2;
}

CC_Dubins_Path::~CC_Dubins_Path()
{
  delete qi1;
  delete qi2;
  delete qi3;
  delete qi4;
  delete cstart;
  delete cend;
  delete ci1;
  delete ci2;
}

void CC_Dubins_Path::print(bool eol) const
{
  cout << "CC_Dubins_Path: type ";
  switch (type)
  {
    case cc_dubins::E:
      cout << "E";
      break;
    case cc_dubins::S:
      cout << "S";
      break;
    case cc_dubins::T:
      cout << "T";
      break;
    case cc_dubins::TT:
      cout << "TT";
      break;
    // Dubins families:
    case cc_dubins::TST:
      cout << "TST";
      break;
    case cc_dubins::TTT:
      cout << "TTT";
      break;
    // #####################
    case cc_dubins::TTTT:
      cout << "TTTT";
      break;
    default:
      cout << "?";
      break;
  }
  cout << ", length " << length << ", configurations ";
  start.print(false);
  cout << " -> ";
  if (qi1)
  {
    qi1->print(false);
    cout << " -> ";
  }
  if (qi2)
  {
    qi2->print(false);
    cout << " -> ";
  }
  if (qi3)
  {
    qi3->print(false);
    cout << " -> ";
  }
  if (qi4)
  {
    qi4->print(false);
    cout << " -> ";
  }
  end.print(false);
  if (eol)
  {
    cout << endl;
  }
}

HC_CC_RS_Path::HC_CC_RS_Path(const Configuration &_start, const Configuration &_end, hc_cc_rs::path_type _type,
                             double _kappa, double _sigma, Configuration *_qi1, Configuration *_qi2,
                             Configuration *_qi3, Configuration *_qi4, HC_CC_Circle *_cstart, HC_CC_Circle *_cend,
                             HC_CC_Circle *_ci1, HC_CC_Circle *_ci2, double _length)
  : Path(_start, _end, _kappa, _sigma, _length)
{
  type = _type;
  qi1 = _qi1;
  qi2 = _qi2;
  qi3 = _qi3;
  qi4 = _qi4;
  cstart = _cstart;
  cend = _cend;
  ci1 = _ci1;
  ci2 = _ci2;
}

HC_CC_RS_Path::~HC_CC_RS_Path()
{
  delete qi1;
  delete qi2;
  delete qi3;
  delete qi4;
  delete cstart;
  delete ci1;
  delete ci2;
  delete cend;
}

void HC_CC_RS_Path::print(bool eol) const
{
  cout << "HC_CC_RS_Path: type ";
  switch (type)
  {
    case hc_cc_rs::E:
      cout << "E";
      break;
    case hc_cc_rs::S:
      cout << "S";
      break;
    case hc_cc_rs::T:
      cout << "T";
      break;
    case hc_cc_rs::TT:
      cout << "TT";
      break;
    case hc_cc_rs::TcT:
      cout << "TcT";
      break;
    // Reeds-Shepp families:
    case hc_cc_rs::TcTcT:
      cout << "TcTcT";
      break;
    case hc_cc_rs::TcTT:
      cout << "TcTT";
      break;
    case hc_cc_rs::TTcT:
      cout << "TTcT";
      break;
    case hc_cc_rs::TST:
      cout << "TST";
      break;
    case hc_cc_rs::TSTcT:
      cout << "TSTcT";
      break;
    case hc_cc_rs::TcTST:
      cout << "TcTST";
      break;
    case hc_cc_rs::TcTSTcT:
      cout << "TcTSTcT";
      break;
    case hc_cc_rs::TTcTT:
      cout << "TTcTT";
      break;
    case hc_cc_rs::TcTTcT:
      cout << "TcTTcT";
      break;
    // #####################
    case hc_cc_rs::TTT:
      cout << "TTT";
      break;
    case hc_cc_rs::TcST:
      cout << "TcST";
      break;
    case hc_cc_rs::TScT:
      cout << "TScT";
      break;
    case hc_cc_rs::TcScT:
      cout << "TcScT";
      break;
    default:
      cout << "?";
      break;
  }
  cout << ", length " << length << ", configurations ";
  start.print(false);
  cout << " -> ";
  if (qi1)
  {
    qi1->print(false);
    cout << " -> ";
  }
  if (qi2)
  {
    qi2->print(false);
    cout << " -> ";
  }
  if (qi3)
  {
    qi3->print(false);
    cout << " -> ";
  }
  if (qi4)
  {
    qi4->print(false);
    cout << " -> ";
  }
  end.print(false);
  if (eol)
  {
    cout << endl;
  }
}

bool state_equal(const State &state1, const State &state2)
{
  if (fabs(state2.kappa - state1.kappa) > get_epsilon())
    return false;
  if (fabs(twopify(state2.theta) - twopify(state1.theta)) > get_epsilon())
    return false;
  if (point_distance(state1.x, state1.y, state2.x, state2.y) > get_epsilon())
    return false;
  return true;
}

void reverse_control(Control &control)
{
  control.delta_s = -control.delta_s;
  control.kappa = control.kappa + fabs(control.delta_s) * control.sigma;
  control.sigma = -control.sigma;
}

Control subtract_control(const Control &control1, const Control &control2)
{
  assert(sgn(control1.delta_s) * control1.sigma == sgn(control2.delta_s) * control2.sigma);
  Control control;
  control.delta_s = control1.delta_s - control2.delta_s;
  control.kappa = control1.kappa;
  control.sigma = control1.sigma;
  return control;
}

void empty_controls(vector<Control> &controls)
{
  Control control;
  control.delta_s = 0.0;
  control.kappa = 0.0;
  control.sigma = 0.0;
  controls.push_back(control);
}

void straight_controls(const Configuration &q1, const Configuration &q2, vector<Control> &controls)
{
  double length = point_distance(q1.x, q1.y, q2.x, q2.y);
  double dot_product = cos(q1.theta) * (q2.x - q1.x) + sin(q1.theta) * (q2.y - q1.y);
  int d = sgn(dot_product);
  Control control;
  control.delta_s = d * length;
  control.kappa = 0.0;
  control.sigma = 0.0;
  controls.push_back(control);
}

int direction(bool forward, bool order)
{
  if ((forward && order) || (!forward && !order))
    return 1;
  else
    return -1;
}

void rs_turn_controls(const HC_CC_Circle &c, const Configuration &q, bool order, vector<Control> &controls)
{
  assert(fabs(fabs(c.kappa) - fabs(q.kappa)) < get_epsilon() &&
         fabs(fabs(c.sigma) - numeric_limits<double>::max()) < get_epsilon());
  double delta = c.deflection(q);
  double length_arc = fabs(c.kappa_inv) * c.rs_circular_deflection(delta);
  int d = direction(c.forward, order);

  Control arc;
  arc.delta_s = d * length_arc;
  arc.kappa = c.kappa;
  arc.sigma = 0.0;
  controls.push_back(arc);
  return;
}

void hc_turn_controls(const HC_CC_Circle &c, const Configuration &q, bool order, vector<Control> &controls)
{
  assert(fabs(fabs(c.kappa) - fabs(q.kappa)) < get_epsilon());
  double delta = c.deflection(q);
  double length_min = fabs(c.kappa / c.sigma);
  double length_arc = fabs(c.kappa_inv) * c.hc_circular_deflection(delta);
  int d = direction(c.forward, order);

  Control clothoid, arc;
  if (order)
  {
    clothoid.delta_s = d * length_min;
    clothoid.kappa = 0.0;
    clothoid.sigma = c.sigma;
    controls.push_back(clothoid);
  }

  arc.delta_s = d * length_arc;
  arc.kappa = c.kappa;
  arc.sigma = 0.0;
  controls.push_back(arc);

  if (!order)
  {
    clothoid.delta_s = d * length_min;
    clothoid.kappa = c.kappa;
    clothoid.sigma = -c.sigma;
    controls.push_back(clothoid);
  }
  return;
}

bool cc_elementary_controls(const HC_CC_Circle &c, const Configuration &q, double delta, bool order,
                            vector<Control> &controls)
{
  double sigma0;
  if (c.cc_elementary_sharpness(q, delta, sigma0))
  {
    double length = sqrt(delta / fabs(sigma0));
    int d = direction(c.forward, order);

    Control clothoid1, clothoid2;
    clothoid1.delta_s = d * length;
    clothoid1.kappa = 0.0;
    clothoid1.sigma = sigma0;
    controls.push_back(clothoid1);

    clothoid2.delta_s = d * length;
    clothoid2.kappa = sigma0 * length;
    clothoid2.sigma = -sigma0;
    controls.push_back(clothoid2);
    return true;
  }
  return false;
}

void cc_default_controls(const HC_CC_Circle &c, const Configuration &q, double delta, bool order,
                         vector<Control> &controls)
{
  double length_min = fabs(c.kappa / c.sigma);
  double length_arc = fabs(c.kappa_inv) * c.cc_circular_deflection(delta);
  int d = direction(c.forward, order);

  Control clothoid1, arc, clothoid2;
  clothoid1.delta_s = d * length_min;
  clothoid1.kappa = 0.0;
  clothoid1.sigma = c.sigma;
  controls.push_back(clothoid1);

  arc.delta_s = d * length_arc;
  arc.kappa = c.kappa;
  arc.sigma = 0.0;
  controls.push_back(arc);

  clothoid2.delta_s = d * length_min;
  clothoid2.kappa = c.kappa;
  clothoid2.sigma = -c.sigma;
  controls.push_back(clothoid2);
  return;
}

void cc_turn_controls(const HC_CC_Circle &c, const Configuration &q, bool order, vector<Control> &controls)
{
  assert(fabs(q.kappa) < get_epsilon());
  double delta = c.deflection(q);
  // delta = 0
  if (delta < get_epsilon())
  {
    if (order)
      straight_controls(c.start, q, controls);
    else
      straight_controls(q, c.start, controls);
    return;
  }
  // 0 < delta < 2 * delta_min
  else if (delta < 2 * c.delta_min)
  {
    vector<Control> controls_elementary, controls_default;
    if (cc_elementary_controls(c, q, delta, order, controls_elementary))
    {
      cc_default_controls(c, q, delta, order, controls_default);
      double length_elementary =
          accumulate(controls_elementary.begin(), controls_elementary.end(), 0.0,
                     [](double sum, const Control &control) { return sum + fabs(control.delta_s); });
      double length_default =
          accumulate(controls_default.begin(), controls_default.end(), 0.0,
                     [](double sum, const Control &control) { return sum + fabs(control.delta_s); });
      (length_elementary < length_default) ?
          controls.insert(controls.end(), controls_elementary.begin(), controls_elementary.end()) :
          controls.insert(controls.end(), controls_default.begin(), controls_default.end());
      return;
    }
    else
    {
      cc_default_controls(c, q, delta, order, controls);
      return;
    }
  }
  // delta >= 2 * delta_min
  else
  {
    cc_default_controls(c, q, delta, order, controls);
    return;
  }
}

} // namespace steering
