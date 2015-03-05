// This is free and unencumbered software released into the public domain.
// For more information, please refer to <http://unlicense.org/>

#ifndef TLSLIBRARIES_TRANSMISSIONLINE_CABLEUNITLOADCALCULATOR_H_
#define TLSLIBRARIES_TRANSMISSIONLINE_CABLEUNITLOADCALCULATOR_H_

#include <list>
#include <string>

#include "base/vector.h"
#include "transmissionline/weather_load_case.h"

/// \par OVERVIEW
///
/// This class generates unit loads for a single transmission cable, subjected
/// to a specific weather load case.
///
/// Unit loads are generated by modeling a cylinder (potentially subjected to
/// radial icing) in a free steam flow.
///
/// \par ASSUMPTIONS
///
/// - uniform loading (constat wind speed, equal ice accumulation)
/// - drag coefficient is 1.0 (no aerodynamic effects)
class CableUnitLoadCalculator {
 public:
  /// \brief Default constructor.
  CableUnitLoadCalculator();

  /// \brief Destructor.
  ~CableUnitLoadCalculator();

  /// \brief Gets the load per unit length of cable.
  /// \param[in] case_load_weather
  ///   The weather load case.
  /// \return The vector load per unit length of cable. X is transverse, Y is
  ///   vertical.
  Vector2d UnitCableLoad(const WeatherLoadCase& case_load_weather) const;

  /// \brief Validates member variables.
  /// \param[in] is_included_warnings
  ///   A flag that tightens the acceptable value range.
  /// \param[in,out] messages_error
  ///   A list of detailed error messages. If this is provided, any validation
  ///   errors will be appended to the list.
  /// \return A boolean value indicating status of member variables.
  bool Validate(const bool& is_included_warnings = true,
                std::list<std::string>* messages_error = nullptr) const;

  /// \brief Gets the diameter of the bare cable.
  /// \return The diameter of the bare cable.
  double diameter_cable() const;

  /// \brief Sets the diameter of the bare cable.
  /// \param[in] diameter_cable
  ///   The diameter of the bare cable.
  void set_diameter_cable(const double& diameter_cable);

  /// \brief Sets the unit weight of the bare cable.
  /// \param[in] weight_unit_cable
  ///   The unit weight of the bare cable.
  void set_weight_unit_cable(const double& weight_unit_cable);

  /// \brief Gets the weight of the bare cable.
  /// \return The unit weight of the bare cable.
  double weight_unit_cable() const;

 private:
  /// \var diameter_cable_
  ///   The diameter of the bare cable.
  double diameter_cable_;

  /// \var weight_unit_cable_
  ///   The weight per unit length of the bare cable.
  double weight_unit_cable_;
};

#endif // TLSLIBRARIES_TRANSMISSIONLINE_CABLEUNITLOADCALCULATOR_H_
