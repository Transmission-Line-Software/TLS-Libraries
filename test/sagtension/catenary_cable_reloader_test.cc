// This is free and unencumbered software released into the public domain.
// For more information, please refer to <http://unlicense.org/>

#include "sagtension/catenary_cable_reloader.h"

#include "gtest/gtest.h"

#include "base/helper.h"
#include "factory.h"

class CatenaryCableReloaderTest : public ::testing::Test {
 protected:
  CatenaryCableReloaderTest() {

    Cable cable = factory::BuildCable();

    Vector3d spacing_endpoints(1200, 0, 0);

    CableState state;
    state.load_stretch = 0;
    state.temperature = 60;
    state.temperature_stretch = 0;

    Vector3d weight_unit(0, 0, 1.094);

    CatenaryCable catenary_cable;
    catenary_cable.set_cable(cable);
    catenary_cable.set_spacing_endpoints(spacing_endpoints);
    catenary_cable.set_state(state);
    catenary_cable.set_tension_horizontal(6000);
    catenary_cable.set_weight_unit(weight_unit);

    // builds dependency object - reloaded state
    CableState state_reloaded;
    state_reloaded.load_stretch = 0;
    state_reloaded.temperature = 60;
    state_reloaded.temperature_stretch = 0;

    // builds dependency object - reloaded unit weight
    Vector3d weight_unit_reloaded(0, 0, 1.094);

    // builds fixture object
    c_.set_catenary_cable(catenary_cable);
    c_.set_state_reloaded(state_reloaded);
    c_.set_weight_unit_reloaded(weight_unit_reloaded);
  }

  CatenaryCableReloader c_;
};

TEST_F(CatenaryCableReloaderTest, LengthUnloadedUnstretched) {

  // unstretched original catenary cable
  EXPECT_EQ(1200.82,
            helper::Round(c_.LengthUnloadedUnstretched(), 2));
}

TEST_F(CatenaryCableReloaderTest, CatenaryCableReloaded) {

  CatenaryCable catenary_cable;
  CableState state = c_.state_reloaded();
  Vector3d weight_unit = c_.weight_unit_reloaded();

  // nothing is modified - original and reloaded parameters are equal
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(6000,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  // tests temperature changes
  state.temperature = 0;
  c_.set_state_reloaded(state);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(6788,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  state.temperature = 212;
  c_.set_state_reloaded(state);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(4702,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  // changes temperature to zero and tests unit weight changes
  state.temperature = 0;
  c_.set_state_reloaded(state);

  weight_unit.set_y(2.072);
  weight_unit.set_z(3.729);
  c_.set_weight_unit_reloaded(weight_unit);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(17126,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  weight_unit.set_y(1.405);
  weight_unit.set_z(2.099);
  c_.set_weight_unit_reloaded(weight_unit);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(12147,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  // sets stretch load and tests all above cases again
  const double kLoadStretch =
      helper::Round(catenary_cable.TensionAverage(100), 0);
  EXPECT_EQ(12179, kLoadStretch);
  state.load_stretch = kLoadStretch;
  c_.set_state_reloaded(state);

  state.temperature = 60;
  c_.set_state_reloaded(state);
  weight_unit.set_y(0);
  weight_unit.set_z(1.094);
  c_.set_weight_unit_reloaded(weight_unit);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(5562,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  state.temperature = 0;
  c_.set_state_reloaded(state);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(6320,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  state.temperature = 212;
  c_.set_state_reloaded(state);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(4528,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  state.temperature = 0;
  c_.set_state_reloaded(state);
  weight_unit.set_y(2.072);
  weight_unit.set_z(3.729);
  c_.set_weight_unit_reloaded(weight_unit);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(17126,
            helper::Round(catenary_cable.tension_horizontal(), 0));

  weight_unit.set_y(1.405);
  weight_unit.set_z(2.099);
  c_.set_weight_unit_reloaded(weight_unit);
  catenary_cable = c_.CatenaryCableReloaded();
  EXPECT_EQ(12147,
            helper::Round(catenary_cable.tension_horizontal(), 0));
}

TEST_F(CatenaryCableReloaderTest, Validate) {

  EXPECT_TRUE(c_.Validate(false, nullptr));
}
