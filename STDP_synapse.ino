// pins
int forward_bias = A0;
int reverse_bias = A1;
int gate = A2;
int cur_out = 10;

double w = 0.5; // inital weight of synapse
float v_f = 0.0;
float v_r =0.0;
float g;

void setup() {
  pinMode(forward_bias,INPUT);
  pinMode(reverse_bias,INPUT);
  pinMode(gate,INPUT);
  pinMode(cur_out,OUTPUT);
  Serial.begin(9600);
}

void loop() {
    analogWrite(cur_out,0);
    Serial.print("Weight ");
    Serial.println(w);
    
    for(int i = 0; i<30; i++){
            v_f += analogRead(forward_bias);
            v_r += analogRead(reverse_bias);
        }
        
    v_f = v_f/30;
    v_r = v_r/30;
    float vf = v_f*5/1024;
    float vr = v_r*5/1024;
    float v_dif = vf - vr;
    v_f = 0;
    v_r = 0;
    g = analogRead(gate);
        
    if ( g > 10 ){
        Serial.print(" v_dif");
        Serial.println( v_dif );
        Serial.print(" GATE: ");
        Serial.println( g );
        if (v_dif > 2.0){
            if (w < 1.0){
                Serial.println("Weight incresed");
                w = w + 0.15;
                }
        }
        if (v_dif <  -1.6 ){ 
            Serial.println("Weight decreases");
            if(w > 0.1) {
            w = w - 0.15;}
            }
        else{
            Serial.println(" Reading... ");
            int curr = abs(v_dif*400) * w * 1.0 ;          
            analogWrite(cur_out,curr);
            delay(10);
            }
  
        }
}
