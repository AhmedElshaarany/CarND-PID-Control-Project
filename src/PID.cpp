#include <uWS/uWS.h>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  //Initialize coefficients
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  is_initialized = false;

  int_cte = 0;
  prev_cte = 0;
  curr_cte = 0;
  n = 0;
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  n = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}
