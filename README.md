# Parking Detection

## Summary
  This code uses an ultra sonic sensor to go through a state machine shown in report written in a paper by Hongmei Zhu, Shengzhong Feng, and Fengqi Yu. Their simulation however, used a magnetic flux sensor so the code written whas conversions of the ultra sonic in order to work similar to the magnetic flux sensor and travel through the state machine the same way. The teams test was a smaller scale between 0cm and 18cm from the ultrasonic sensor.

## General Functionality
 This code uses a switch statement to go through the state machine keeping the system in the state until current state variable changes then switches to different case in state machine. Switches between Initial state, Vacant and Occupied states, Interm States, and Critical states. The initial state is the initial state of the system which can be transfered out with a put of the button, going from vacant to interium states for determining if a person is parking in this case it is small scale with code only having 18cm range. Will use same conditions as given state machine which can be located in the link below. The critical states are special however constants were set to reduce noise for the flags used with small range if in this range will enter critical state will only exit state if outside of the range. Exiting and entering the Vacant and Occupied states is determined by values Thavl and Thdpt which compares the values taken from the distance function which is taking the measurements from the ultrasonic sensor. For Vacancy if the distance between ultrasonic sensor and closest object is reduced past the Thavl constant it will transition to the interium possibly switching to the occuppied state after a ceratin amount of time. The same is said with occupency except if the closes object is further than the constant Thdpt it will switch to interium until time runs out or the measured distance increase back to higher than Thdpt. In order to work the same way as the state machine since they referenced the high magnetic flux when a car parked rather than how close the closest object is to the sensor the highest value possible for the ultra sonic sensor 2300 was subtracted from the wanted values of distance making lets say 3cm to 2297 higher than 18cm or 2282. 
 
## Inputs and Outputs

### Inputs:  
  • Pin 52 = Button Input starting system transitions out of initial state  
  • Pin 11 = Echo pin of Utra sonic sensor  
  • Pin 12 = Trigger pin of Ultra sonic sensor  
### Displayed Outputs:
  • Current State: Outputs the current state system is in keeping track of state machine transition
  
## Authors

   Author: Kieran O'Connor and Shane Price  
   Last Editted: 4/30/2019

### References

Parking Detection Method Based on Finite-State Machine and Collaborative Decision-Making:https://ieeexplore.ieee.org/document/8471111/figures#figures
