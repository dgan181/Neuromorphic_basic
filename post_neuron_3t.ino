// pins
int drive = 9;
int feedback = 10;
int ledPin = 7;
int ext_fire = 2;
int v_input = 11;
int cur_input_0 = A0;
int cur_input_1 = A2;

float v_th = 1.0; // threshold voltage
float v_rest = 0.0; // reset voltage

float dt = 0.1 ;// seconds
float t_rest = 0;
int t_ref = 1000;// refractory period; not in seconds

// variables
int d;
float v = 0;
float I1 = 0;
float I2 = 0;
float I = 0;

// pulse parameters
float vread = 0.5;
float vplus = 3;
float vmins = 2;

int vread_a = vread*255/5;
int vplus_a = vplus*255/5;
int vmins_a = vmins*255/5;

void generate(); // generates output and feedback pulses

void setup() {
    pinMode(drive, OUTPUT);
    pinMode(feedback, OUTPUT);
    pinMode(v_input, OUTPUT);
    pinMode(cur_input_0, INPUT);
    pinMode(cur_input_1, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(ext_fire,INPUT);
}

void loop() {
    analogWrite(feedback,0);
    analogWrite(v_input,vread_a ); 
    
    // post neuron receives two inputs
    I1 = analogRead(cur_input_0);
    I2 = analogRead(cur_input_1);
    I = (I1+I2)/500;
    d = digitalRead(ext_fire);
    
    if (t_rest == 0){ 
        if (v >= v_th-0.01 || d){ // firing
            v = v_rest;
            //Serial.println("LED ON");
            t_rest = t_ref;
            digitalWrite(ledPin, HIGH);
            generate(vplus_a,vmins_a);
            digitalWrite(ledPin, LOW);
            }
        else{ // accumulation
            v = v + dt*(-v + I);
            }
        }
    else{ // refractory period
      t_rest = t_rest - 1;
      v = v_rest;
        }

}

// generates output and feedback pulses
void generate(float vplus ,float vmins){
    analogWrite(drive,255);
    analogWrite(feedback,vplus);
    analogWrite(v_input,0);
    delay(100);
    analogWrite(feedback,0);
    delay(250);
    analogWrite(drive,0);
    delay(50);
    analogWrite(feedback,0);
    analogWrite(v_input,vmins);
    delay(100);
    analogWrite(feedback,0);
    analogWrite(v_input,0);
    return ;
}
