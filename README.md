# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Finding the PID Coefficient Values

To determine the values of the PID coefficients that would make the car drive safely around the track, a combination of manual tuning and the twiddle algorithm was used to minimize the mean squared cross-track error.

### Proportional Coefficient Kp
The proportional term of the PID equation generates an output value proportional to the current value of the error. The cofficient must not be too low or else the response of the system will be too slow, and not too high or else the system will repsond to the smallest of changes. When setting in Kp to a small value, the car did not respond fast enough to stay on track. When Kp was set to a large value, the car kept going left and right with a high frequency.

### Integral Coefficient Ki
This term contributes a value proportional to the magnitude of the error and its duration. The error is summed over time and provides the error offset that should have been corrected earlier. This term usually makes up for a systematic bias in the steering angle of the car's wheels. The value of Ki for this project is very small, which indicates that there is almost zero systematic bias.

### Derivate Coefficient Kd
The derivative term is determined by the slope of error of time multiplied by the derivative coefficient. This term is used to avoid overshooting in terms of the system's response to the error. Having a small Kd value will cause the car to oscillate. On the other hand, a Kd value that is to large will cause the system to be sensitive to small error changes.

## Final PID Values

1. Kp = 0.25
2. Ki = 0.003
3. Kd = 2.5
