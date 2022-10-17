/*
  Event.h

  Takes as its input one or more electrons in a magnetic field, propagates them, calculates their
  induced voltages on one or more antennas and performs some basic signal processing
*/

#ifndef EVENT_H
#define EVENT_H

#include "EventGeneration/ParticleState.h"
#include "ElectronDynamics/BaseField.h"
#include "ElectronDynamics/BorisSolver.h"
#include "Antennas/IAntenna.h"
#include "EventGeneration/OutputVars.h"

#include "TTree.h"

#include <vector>

namespace rad
{
  class Event
  {
  public:
    /// Parametrised constructor
    /// \param particles A vector of the various particle states one wishes to propagate
    /// \param antennas A vector of the antennas at which signals are generated
    /// \param field The magnetic field in which the particles are propagated
    /// \param simStepSize The time step size to use in the simulation (in seconds)
    /// \param simTime Total time for particles to be simulated for (in seconds)
    Event(std::vector<ParticleState> particles, std::vector<IAntenna *> antennas,
          BaseField *field, double simStepSize, double simTime);

    /// Parametrised constructor
    /// \param particles A vector of the various particle states one wishes to propagate
    /// \param field The magnetic field in which the particles are propagated
    /// \param simStepSize The time step size to use in the simulation (in seconds)
    /// \param simTime Total time for particles to be simulated for (in seconds)
    Event(std::vector<ParticleState> particles, BaseField *field,
          double simStepSize, double simTime);

    /// Propagates the particles for the time specified at construction
    /// \param outputFile The output file directory. Leave as default to write no ouput
    /// \param vars A vector containing the variables to be written to file
    void PropagateParticles(const char *outputFile = NULL, std::vector<OutputVar> vars = {});

    /// Gives the clock time of the event
    /// \Returns The Event clock time (in seconds)
    double GetClockTime() { return clockTime; }

    /// Get the state for one of the particles in the Event
    /// \param particleIndex Index of particle we wish to return
    /// \return A copy of the selected ParticleState
    ParticleState GetParticle(int particleIndex);

    /// Gets the number of particles in a given event, active or inactive
    /// \return  Number of particles in event
    unsigned int GetNParticles();

  private:
    /// Vector of particles
    std::vector<ParticleState> particleList;

    /// Vector of solvers corresponding to the particles
    std::vector<BorisSolver> solverList;

    /// Vector of antennas for signals to be generated on
    std::vector<IAntenna *> antennaList;

    double clockTime;
    double simulationStepSize;
    double maximumSimulationTime;
    BaseField *magneticField;

    // These arrays are only used for writing outputs
    double pos[3];
    double vel[3];
    double acc[3];
    double bField[3];

    /// Checks if a particle has started relative to the Event clock time
    /// \param part The particle which we are checking if it has started
    /// \Returns True if the particle should be being propagated
    bool ParticleStartCheck(ParticleState part);

    /// Moves a given particle forward one step in time (according to the supplied time step)
    /// \param particleNumber The index of the particle in the event to be propagated
    void AdvanceParticleStep(int particleNumber);

    /// Calculates the light propagation time between a particle and an antenna point
    /// \param particle The particle in question
    /// \param antenna The selected antenna
    /// \Return The light propagation time in seconds
    double GetPropagationTime(ParticleState particle, IAntenna *antenna);

    /// Creates an output tree with the desired variables in it
    /// \param vars Vector containing the desired output variables
    /// \return A TTree with the desired variables as branches
    TTree *CreateOutputTree(std::vector<OutputVar> vars);

    /// Adds the data from the particle state to the TTree
    /// \param outputTree The tree to add the data to
    /// \param vars The variables to write to the TTree
    void AddParticleData(TTree *outputTree, std::vector<OutputVar> vars);
  };
}

#endif
