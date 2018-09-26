const int DIG_D = 5;
const int DIG_C = 4;
const int DIG_B = 3;
const int DIG_A = 2;

const int LATCH_H1 = 9;
const int LATCH_H2 = 10;
const int LATCH_M1 = 11;
const int LATCH_M2= 12;

int incomingByte = 0;
int my_int;
int received_integer = 0;
int nDigits = 0;

int * array_of_time_arduino = new int[4];
int * array_of_time_pi = new int[4];

int availableMemory() {
  int size = 1024; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);

  return size;
}

int * convertNumberIntoArray(unsigned int number) {
    int length = (int)floor(log10((float)number)) + 1;
    int * arr = new int[length];
    int i = 0;
    do {
        arr[i] = number % 10;
        number /= 10;
        i++;
    } while (number != 0);
    return arr;
}

void convertIntegerToDCBA(int my_int) {
  if (my_int == 0) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, LOW);
  } else if (my_int == 1) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, HIGH);    
  } else if (my_int == 2) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, HIGH);
    digitalWrite(DIG_A, LOW);
  } else if (my_int == 3) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, HIGH);
    digitalWrite(DIG_A, HIGH);
  } else if (my_int == 4) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, HIGH);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, LOW);
  } else if (my_int == 5) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, HIGH);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, HIGH);
  } else if (my_int == 6) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, HIGH);
    digitalWrite(DIG_B, HIGH);
    digitalWrite(DIG_A, LOW);
  } else if (my_int == 7) {
    digitalWrite(DIG_D, LOW);
    digitalWrite(DIG_C, HIGH);
    digitalWrite(DIG_B, HIGH);
    digitalWrite(DIG_A, HIGH);
  } else if (my_int == 8) {
    digitalWrite(DIG_D, HIGH);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, LOW);
  } else if (my_int == 9) {
    digitalWrite(DIG_D, HIGH);
    digitalWrite(DIG_C, LOW);
    digitalWrite(DIG_B, LOW);
    digitalWrite(DIG_A, HIGH);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // decoder latch pins
  pinMode(LATCH_M1, OUTPUT);
  pinMode(LATCH_M2, OUTPUT);
  pinMode(LATCH_H1, OUTPUT);
  pinMode(LATCH_H2, OUTPUT);

  // decoder input pins
  pinMode(DIG_A, OUTPUT);
  pinMode(DIG_B, OUTPUT);
  pinMode(DIG_C, OUTPUT);
  pinMode(DIG_D, OUTPUT);

}

int lengthOfArray(int my_integer_array) {
  return floor(log10(abs(my_integer_array))) + 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    received_integer = Serial.parseInt();
    nDigits = lengthOfArray(received_integer);

    if(nDigits < 4) {
      array_of_time_pi = convertNumberIntoArray(received_integer);

      array_of_time_arduino[3] = 0;
      array_of_time_arduino[0] = array_of_time_pi[0];
      array_of_time_arduino[1] = array_of_time_pi[1];
      array_of_time_arduino[2] = array_of_time_pi[2];

      digitalWrite(LATCH_M1, LOW);
      convertIntegerToDCBA(array_of_time_arduino[3]);
      digitalWrite(LATCH_M1, HIGH);

      digitalWrite(LATCH_M2, LOW);
      convertIntegerToDCBA(array_of_time_arduino[2]);
      digitalWrite(LATCH_M2, HIGH);

      digitalWrite(LATCH_H1, LOW);
      convertIntegerToDCBA(array_of_time_arduino[1]);
      digitalWrite(LATCH_H1, HIGH);

      digitalWrite(LATCH_H2, LOW);
      convertIntegerToDCBA(array_of_time_arduino[0]);
      digitalWrite(LATCH_H2, HIGH);
    
    } else {
      array_of_time_pi = convertNumberIntoArray(received_integer);

      array_of_time_arduino[0] = array_of_time_pi[0];
      array_of_time_arduino[1] = array_of_time_pi[1];
      array_of_time_arduino[2] = array_of_time_pi[2];
      array_of_time_arduino[3] = array_of_time_pi[3];

      digitalWrite(LATCH_M1, LOW);
      convertIntegerToDCBA(array_of_time_arduino[3]);
      digitalWrite(LATCH_M1, HIGH);

      digitalWrite(LATCH_M2, LOW);
      convertIntegerToDCBA(array_of_time_arduino[2]);
      digitalWrite(LATCH_M2, HIGH);

      digitalWrite(LATCH_H1, LOW);
      convertIntegerToDCBA(array_of_time_arduino[1]);
      digitalWrite(LATCH_H1, HIGH);

      digitalWrite(LATCH_H2, LOW);
      convertIntegerToDCBA(array_of_time_arduino[0]);
      digitalWrite(LATCH_H2, HIGH);
    
    }
    delay(500);

  }
  
}
