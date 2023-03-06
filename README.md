# Double Pendulum Simulation in C++

<p align="center">
<img src="https://github.com/Alexander-Rus/double_pendulum/blob/main/img/output-2023-03-06_10_42_17_edit_AdobeExpress%20(1).gif?raw=true"
  alt="Pendulum Sim"
</p>


This program demonstrates a double pendulum simulation in C++ and SFML. Using our simulation in C++, we can visualize the path the second pendulum weight takes as it is affected by the motion of the first pendulum.

A double pendulum is a good example of a chaotic system, as very slight changes in the initial conditions can lead to dramatically different outcomes in how the pendulums swing. The pendulums are primarily affected by the mass of the weights, the length of the rods/strings, gravity, and then angle of release. In the real world, there is also air resistance and friction to consider. 

Though the simulation may appear to be random each time, this system is actually only chaotic because one could, given enough information, calculate the position of the bodies at a given time. 
