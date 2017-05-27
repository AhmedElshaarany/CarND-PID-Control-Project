#include <uWS/uWS.h>
#include "PID.h"

#define ITERATIONS 1000
#define TOLERANCE 0.15
#define NUM_COEFF 3

using namespace std;

/*
* PID class.
*/

/*
 * Class Constructor
 */
PID::PID() {}

/*
 * Class Destructor
 */
PID::~PID() {}

/*
 * PID initialize function
 */
void PID::Init(double Kp, double Ki, double Kd) {
  //Initialize coefficients
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  is_cte_initialized = false;

  // initialize cte values and number of iterations
  int_cte = 0;
  prev_cte = 0;
  curr_cte = 0;
  n = 0;

  // initialize coefficient error values
  p_error = 0.01;
  i_error = 0.001;
  d_error = 0.2;

  // initialize tuning flag, state, and current coefficient
  is_tuned = false;
  state = 0;
  coeff = 0;

  // initialize error variables
  best_error = 0;
  curr_error = 0;
}

/*
 * PID initialize cte values
 */
void PID::InitCTE(double cte){

  // initialize PID cte values
  int_cte = cte;
  prev_cte = cte;
  curr_cte = cte;
  is_cte_initialized = true;
}

/*
 * PID Update Coefficient Error using Twiddle Algorithm
 */
void PID::UpdateError(double cte, uWS::WebSocket<uWS::SERVER> ws) {

  // use a finite state machine to build twiddle
  
  // check state
  switch(state){
    
  // state 0: get initial best error
  case 0:
    if( n < ITERATIONS ){
      best_error += cte*cte;
      n++;
      std::cout << " n = " << n << std::endl;
      std::cout << "State = " << state << std::endl;
    }
    else{
      // get mean error
      best_error /= ITERATIONS;
      
      // move to next state
	state = 1;
    }
    break;

  // state 1: update coefficient and restart
  case 1:
    switch(coeff){
    case 0:
      Kp += p_error;
      break;
    case 1:
      Ki += i_error;
      break;
    case 2:
      Kd += d_error;
      break;
    }
    // move to next state
    state = 2;
    // restart simulator
    Restart(ws);
    break;
      
  // state 2: get new error
  case 2:
    if( n < ITERATIONS ){
      curr_error += cte*cte;
      n++;
    }
    else if((curr_error/ITERATIONS) < best_error){
      // update best error
      best_error = curr_error/ITERATIONS;
      
      // update coefficient error
      switch(coeff){
      case 0:
	p_error *= 1.1;
	break;
      case 1:
	i_error *= 1.1;
	break;
      case 2:
	d_error *= 1.1;
	break;
      }
      
      // move to next coefficient
      state = 1;
      coeff = (coeff + 1)%NUM_COEFF;
    }
    else{
      switch(coeff){
      case 0:
	Kp -= 2*p_error;
	break;
      case 1:
	Ki -= 2*i_error;
	break;
      case 2:
	Kd -= 2*d_error;
	break;
      }
      // move to next state
      state = 3;
      Restart(ws);
    }
    break;

  //state 3: get error
  case 3:
    if( n < ITERATIONS ){
      curr_error += cte*cte;
      n++;
    }
    else if((curr_error/ITERATIONS) < best_error){
      // update best error
      best_error = curr_error/ITERATIONS;
      
      // update coefficient error
      switch(coeff){
      case 0:
	p_error *= 1.1;
	break;
      case 1:
	i_error *= 1.1;
	break;
      case 2:
	d_error *= 1.1;
	break;
      }
      
      // move to next coefficient
      state = 1;
      coeff = (coeff + 1)%NUM_COEFF;
    }
    else{
      switch(coeff){
      case 0:
	Kp += p_error;
	p_error *= 0.9;
	break;
      case 1:
	Ki += i_error;
	i_error *= 0.9;
	break;
      case 2:
	Kd += d_error;
	d_error *= 0.9;
	break;
      }

      // move to next iteration
      state = 1;
      coeff = (coeff + 1)%NUM_COEFF;
    }
    break;
  }
  
  // check if tolerance achieved
  if(TotalError() <= TOLERANCE && coeff == 2){
    is_tuned = true;
  }

  
}

/*
 * PID Total Error Calculation
 */
double PID::TotalError() {

  // return sum of coefficient error values
  return p_error + i_error + d_error;
}


/*
 * PID Reset and Restart the simulator
 */
void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){

  // reset variables
  n = 0;
  int_cte = 0;
  prev_cte = 0;
  curr_cte = 0;
  curr_error = 0;

  // restart the simulator
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}
