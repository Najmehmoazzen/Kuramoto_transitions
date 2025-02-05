# Kuramoto Transitions

## Overview
This repository contains implementations of both first-order and second-order phase transitions in Kuramoto oscillator networks. The code simulates time series of phase evolution and computes synchronization parameters over time.

## Kuramoto Model
The Kuramoto model describes a system of coupled oscillators evolving according to the equation:

$$
\frac{d\theta_i}{dt} = \omega_i +K \sum_{j}  A_{ij} \sin(\theta_j - \theta_i)
$$

where:
- \($$\theta_i\$$) is the phase of the \($$i\$$)th oscillator.
- \($$\omega_i\$$) is its natural frequency.
- \($$K\$$) is the global coupling strength.
- \($$A_{ij}\$$) is the adjacency matrix defining the network topology.

## Phase Transitions
### First-Order Transition
- Occurs in a network of **100 nodes**.
- There is a **correlation between node degree and natural frequency**.
- The transition exhibits a discontinuous jump in the order parameter.

### Second-Order Transition
- Occurs in an **all-to-all network** with **100 nodes**.
- The order parameter changes **continuously** as coupling strength increases.

## Data Storage
- **Time series of phases**: Tracks the evolution of each oscillator’s phase over time.
- **Synchronization parameters vs time**: Measures global synchronization dynamics.

