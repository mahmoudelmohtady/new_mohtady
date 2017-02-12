void Inv_Kin() {
  // Calculation Factors
  a = (sb / 2) - (sp / 2);
  b = sb * sqrt(3) / 6 - sp * sqrt(3) / 6 ;
  c = sp * sqrt(3) / 3 - sb * sqrt(3) / 3 ;
  //-----------------------------------------------------------------------------------------------------------

  //From vector loop closure equation
  c1 = pow(x, 2) + pow(y, 2 ) + pow(z, 2) + pow(a, 2) + pow(b, 2) + (2 * a * x) + (2 * b * y ) - pow(l, 2) ;
  c2 = pow(x, 2) + pow(y, 2 )  + pow(z, 2) + pow(a, 2) + pow(b, 2) - 2 * a * x + 2 * b * y - pow(l, 2);
  c3 = pow(x, 2) + pow(y, 2)   + pow(z, 2) + pow(c, 2) + 2 * c * y - pow(l, 2) ;
  //------------------------------------------------------------------------------------------------------------

  // L1 soulutions equation
  L11 = -z + sqrt(pow(z, 2) - c1 ) ;
  L12 = -z - sqrt(pow(z, 2) - c1 ) ;
  //Using lower position of legs
  if (L11 < L12)
    L1  = L11;
  else {
    L1 = L12;
  }
  //----------------------------------------------------------------------------------------------------------

  // L2 soulutions equation
  L21 = -z + sqrt(pow(z, 2) - c2 ) ;
  L22 = -z - sqrt(pow(z, 2) - c2 ) ;
  //Using lower position of legs
  if (L21 < L22)
    L2  = L21;
  else {
    L2 = L22;
  }
  //----------------------------------------------------------------------------------------------------------

  // L3 soulutions equation
  L31 = -z + sqrt(pow(z, 2) - c3 ) ;
  L32 = -z - sqrt(pow(z, 2) - c3 ) ;
  //Using lower position of legs
  if (L31 < L32) {
    L3  = L31;
  }
  else L3 = L32;
  //----------------------------------------------------------------------------------------------------------

  //Calculate the required travel from the current position

  Ln1 = L1 - Lp1 ;
  Ln2 = L2 - Lp2 ;
  Ln3 = L3 - Lp3 ;

  // Saving Absolute carriage travel to the next position "for upcoming orders"
  Lp1 = L1 ;
  Lp2 = L2 ;
  Lp3 = L3 ;
  //-----------------------------------------------------------------------------------------------------------
  // **********************************Number of steps calculator**********************************************
  // Conversion from travel in (mm) to travel in (steps)

  S1 = ((Lp1 / 11.25) * DS) / (2 * pi);
  S2 = ((Lp2 / 11.25) * DS) / (2 * pi);
  S3 = ((Lp3 / 11.25) * DS) / (2 * pi);
  // Practical wise  direction of motors"Due to current setup configuartion"
  S3 = -S3 ;
  S2 = -S2 ;


}
