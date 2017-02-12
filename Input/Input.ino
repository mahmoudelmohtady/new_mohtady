void Input() {
  // Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter the required end-effector position & velocity seperated by a comma: X,y,Z,Xv,Yv,Zv ");
  Serial.print("Enter Move Values Now: ");
  
  if (move_finished == 1) {
    while (!Serial.available()) ; // hang program until a byte is received notice the
    //move_finished = 0;            // Reset variable for checking move of the Steppers

    x = Serial.readString().toFloat();       // Put First numeric value from buffer in Travel1 variable
    Serial.print(x);
    Serial.print("  x , ");
    Serial.flush();
    
    while (!Serial.available()) ; // hang program until a byte is received notice the
    y = Serial.readString().toFloat(); // Put Second numeric value from buffer in Travel2 variable
    Serial.print(y);
    Serial.print("  y ,");
    Serial.flush();
    
    while (!Serial.available()) ; // hang program until a byte is received notice the
    z = Serial.readString().toFloat(); // Put Second numeric value from buffer in Travel3 variable
    Serial.print(z);
    Serial.print(" z \n ");
    Serial.flush();
    
    while (!Serial.available()) ; // hang program until a byte is received notice the

    Xv = Serial.readString().toFloat(); // Put Second numeric value from buffer in Travel3 variable
    Serial.print(Xv);
    Serial.print(" Xv , ");
    Serial.flush();
    while (!Serial.available()) ; // hang program until a byte is received notice the

    Yv = Serial.readString().toFloat(); // Put Second numeric value from buffer in Travel3 variable
    Serial.print(Yv);
    Serial.print(" Yv , ");
    Serial.flush();
    
    while (!Serial.available()) ; // hang program until a byte is received notice the
    Zv = Serial.readString().toFloat(); // Put Second numeric value from buffer in Travel3 variable
    Serial.print(Zv);
    Serial.print(" Zv \n");
    Serial.flush();          //Clear all data on serial
  }
}

